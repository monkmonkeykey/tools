#!/usr/bin/env python3

from luma.core.interface.serial import i2c
from luma.core.render import canvas
from luma.oled.device import ssd1306
from PIL import ImageFont

from pathlib import Path
import sys
import subprocess
import json
import time
import os
import struct
import pwd
import grp

import sys
import os
from pathlib import Path

# =========================================================
# AUTODETECCIÓN Y AUTOACTIVACIÓN DE VENV
# =========================================================
VENV_PYTHON = Path(__file__).parent / "venv" / "bin" / "python3"

if VENV_PYTHON.exists() and Path(sys.executable).resolve() != VENV_PYTHON.resolve():
    print(f"[SISTEMA] Relanzando script dentro del entorno virtual: {VENV_PYTHON}")
    os.execv(str(VENV_PYTHON), [str(VENV_PYTHON)] + sys.argv)
    
# =========================================================
# CONFIGURACION
# =========================================================

DESTINO_DIR = Path("/home/pi/Documents/rnbo/datafiles")
DESTINO_FILE = DESTINO_DIR / "archivoAReproducir.wav"
MOUNT_BASE = Path("/mnt/rnbo-usb")
ESPERA_ANTES_COPIA = 5
CHUNK_SIZE = 1024 * 1024


# =========================================================
# OLED
# =========================================================

serial = i2c(port=1, address=0x3C)
device = ssd1306(serial, width=128, height=64)
font = ImageFont.load_default()


def mostrar(*lineas):
    """Muestra hasta 6 líneas en la OLED."""
    with canvas(device) as draw:
        y = 0
        for linea in lineas[:6]:
            draw.text((0, y), str(linea), font=font, fill="white")
            y += 10


def cortar(texto, longitud=20):
    texto = str(texto)
    if len(texto) <= longitud:
        return texto
    return texto[:longitud - 3] + "..."


def formato_tamano(numero_bytes):
    mb = numero_bytes / (1024 * 1024)
    if mb < 1024:
        return f"{mb:.1f} MB"
    return f"{mb / 1024:.2f} GB"


# =========================================================
# TRANSICIÓN AL SCRIPT DE CONTROL (info.py)
# =========================================================

def ejecutar_info_script():
    """
    Reemplaza el proceso actual por el script info.py sin requerir un reboot.
    """
    info_path = Path(__file__).parent / "info.py"
    if info_path.exists():
        print(f"[SISTEMA] Iniciando {info_path}...")
        try:
            device.clear()
        except Exception:
            pass
        # os.execv reemplaza la ejecución de inicio.py por info.py
        os.execv(sys.executable, [sys.executable, str(info_path)])
    else:
        print(f"[ERROR] No se encontró el script de control: {info_path}")
        sys.exit(1)


# =========================================================
# LECTURA DE CANALES WAV
# =========================================================

def canales_wav(archivo):
    try:
        with open(archivo, "rb") as f:
            cabecera = f.read(12)
            if len(cabecera) < 12 or cabecera[0:4] not in (b"RIFF", b"RF64") or cabecera[8:12] != b"WAVE":
                return "?"

            while True:
                chunk_header = f.read(8)
                if len(chunk_header) < 8:
                    break
                chunk_id = chunk_header[0:4]
                chunk_size = struct.unpack("<I", chunk_header[4:8])[0]

                if chunk_id == b"fmt ":
                    datos = f.read(min(chunk_size, 64))
                    if len(datos) >= 4:
                        return struct.unpack("<H", datos[2:4])[0]
                    break
                f.seek(chunk_size + (chunk_size % 2), 1)
    except Exception as error:
        print(f"[AVISO] No se pudieron leer canales: {error}")
    return "?"


# =========================================================
# MONTAJE Y DETECCIÓN USB
# =========================================================

def leer_lsblk():
    comando = ["lsblk", "-J", "-o", "NAME,PATH,TRAN,TYPE,FSTYPE,LABEL,UUID,SIZE,MOUNTPOINTS"]
    resultado = subprocess.run(comando, capture_output=True, text=True, check=True)
    return json.loads(resultado.stdout)


def obtener_mountpoint(nodo):
    puntos = nodo.get("mountpoints")
    if not puntos:
        return None
    if isinstance(puntos, str):
        puntos = [puntos]
    for punto in puntos:
        if punto:
            return Path(punto)
    return None


def obtener_discos_usb():
    datos = leer_lsblk()
    return [nodo for nodo in datos.get("blockdevices", []) if nodo.get("type") == "disk" and nodo.get("tran") == "usb"]


def obtener_volumenes(disco):
    volumenes = [hijo for hijo in disco.get("children", []) if hijo.get("type") == "part" and hijo.get("fstype")]
    if not volumenes and disco.get("fstype"):
        volumenes.append(disco)
    return volumenes


def montar_volumen(disco, volumen):
    existente = obtener_mountpoint(volumen)
    if existente and existente.exists():
        return existente

    punto = MOUNT_BASE / f"{disco.get('name', 'usb')}-{volumen.get('name', 'vol')}"
    punto.mkdir(parents=True, exist_ok=True)

    dispositivo = volumen.get("path")
    if not dispositivo:
        return None

    resultado = subprocess.run(["mount", "-o", "ro", dispositivo, str(punto)], capture_output=True, text=True)
    if resultado.returncode != 0:
        return None
    return punto


def buscar_wavs(ruta):
    archivos = []
    try:
        for raiz, directorios, nombres in os.walk(ruta):
            directorios[:] = [d for d in directorios if not d.startswith(".")]
            for nombre in nombres:
                if nombre.startswith("."):
                    continue
                archivo = Path(raiz) / nombre
                if archivo.suffix.lower() == ".wav":
                    archivos.append(archivo)
    except Exception as error:
        print(f"[ERROR BUSCANDO WAV] {ruta}: {error}")
    return sorted(archivos, key=lambda x: str(x).lower())


def analizar_usb(disco):
    nombre = disco.get("label") or disco.get("name") or "USB"
    volumenes = obtener_volumenes(disco)
    todos_los_wavs = []

    for volumen in volumenes:
        punto = montar_volumen(disco, volumen)
        if punto is None:
            continue
        todos_los_wavs.extend(buscar_wavs(punto))

    return {"disk": disco, "name": nombre, "wavs": todos_los_wavs}


def encontrar_usb_valido():
    discos = obtener_discos_usb()
    if not discos:
        return {"estado": "sin_usb"}

    resultados = [analizar_usb(disco) for disco in discos]
    validos = [r for r in resultados if len(r["wavs"]) == 1]

    if len(validos) == 1:
        usb = validos[0]
        return {"estado": "ok", "usb": usb, "archivo": usb["wavs"][0], "resultados": resultados}
    if len(validos) > 1:
        return {"estado": "varios_validos", "cantidad": len(validos), "resultados": resultados}
    return {"estado": "ninguno_valido", "resultados": resultados}


def cambiar_propietario_pi(ruta):
    try:
        uid = pwd.getpwnam("pi").pw_uid
        gid = grp.getgrnam("pi").gr_gid
        os.chown(ruta, uid, gid)
    except Exception as error:
        print(f"[AVISO CHOWN] {error}")


def copiar_archivo(origen, destino, nombre_usb, canales):
    total = origen.stat().st_size
    copiado = 0
    temporal = destino.with_name("." + destino.name + ".tmp")

    if temporal.exists():
        temporal.unlink()

    try:
        with open(origen, "rb") as entrada, open(temporal, "wb") as salida:
            while True:
                bloque = entrada.read(CHUNK_SIZE)
                if not bloque:
                    break
                salida.write(bloque)
                copiado += len(bloque)
                porcentaje = (copiado / total * 100) if total else 100

                mostrar(
                    f"USB: {cortar(nombre_usb, 15)}",
                    "Copiando...",
                    cortar(origen.name, 20),
                    f"{porcentaje:5.1f}%",
                    f"{formato_tamano(copiado)}/{formato_tamano(total)}",
                    f"CH: {canales}"
                )

            salida.flush()
            os.fsync(salida.fileno())

        os.replace(temporal, destino)
        cambiar_propietario_pi(destino)
        os.sync()
    except Exception:
        if temporal.exists():
            temporal.unlink()
        raise


def buscar_nodo_dispositivo(nodos, ruta):
    for nodo in nodos:
        if nodo.get("path") == ruta:
            return nodo
        encontrado = buscar_nodo_dispositivo(nodo.get("children", []), ruta)
        if encontrado:
            return encontrado
    return None


def obtener_montajes_usb(nodo):
    montajes = []
    for hijo in nodo.get("children", []):
        montajes.extend(obtener_montajes_usb(hijo))
    punto = obtener_mountpoint(nodo)
    if punto:
        montajes.append({"device": nodo.get("path"), "mountpoint": punto})
    return montajes


def expulsar_usb(ruta_disco):
    mostrar("Copia completa", "", "Peparando USB", "", "No retire aun", "")
    os.sync()
    datos = leer_lsblk()
    nodo_usb = buscar_nodo_dispositivo(datos.get("blockdevices", []), ruta_disco)

    if nodo_usb is None:
        return

    montajes = obtener_montajes_usb(nodo_usb)
    for montaje in montajes:
        res = subprocess.run(["umount", montaje["device"]], capture_output=True, text=True)
        if res.returncode != 0:
            subprocess.run(["umount", str(montaje["mountpoint"])], capture_output=True, text=True)

    os.sync()


def usb_conectado(ruta_disco):
    try:
        return any(d.get("path") == ruta_disco for d in obtener_discos_usb())
    except Exception:
        return False


def esperar_retiro_usb(ruta_disco):
    while usb_conectado(ruta_disco):
        mostrar("Copia completa", "USB Expulsada", "", "Retire USB", "", "Continuando...")
        time.sleep(0.5)


# =========================================================
# PREPARAR DIRECTORIOS
# =========================================================

DESTINO_DIR.mkdir(parents=True, exist_ok=True)
MOUNT_BASE.mkdir(parents=True, exist_ok=True)
cambiar_propietario_pi(DESTINO_DIR)

ultimo_archivo = None

# =========================================================
# LOOP PRINCIPAL
# =========================================================

while True:
    try:
        resultado = encontrar_usb_valido()
        estado = resultado["estado"]

        # =================================================
        # CASO 1: NO HAY USB
        # =================================================
        if estado == "sin_usb":
            usb_aparecio = False

            for segundos in range(5, 0, -1):
                mostrar("Iniciando Sistema", "", "Buscando USB...", "", f"Espera: {segundos}s", "")
                print(f"Buscando USB. Esperando {segundos}s...")
                time.sleep(1)

                if obtener_discos_usb():
                    usb_aparecio = True
                    break

            if usb_aparecio:
                continue

            # Si transcurrieron los 5s sin USB, pasa a info.py
            mostrar("USB NO Detectado", "", "Cargando", "", "", "")
            time.sleep(1.5)
            ejecutar_info_script()

        # =================================================
        # CASO 2: VARIOS USB VALIDOS
        # =================================================
        if estado == "varios_validos":
            mostrar("Atencion", "", "Varios USB", "Tienen 1 WAV", "", "No se copia")
            time.sleep(2)
            continue

        # =================================================
        # CASO 3: NINGÚN USB VÁLIDO
        # =================================================
        if estado == "ninguno_valido":
            resultados = resultado["resultados"]
            if not resultados:
                time.sleep(1)
                continue

            primero = resultados[0]
            cantidad = len(primero["wavs"])

            if cantidad == 0:
                mostrar(f"USB: {cortar(primero['name'], 15)}", "", "No hay WAV", "", "Debe contener", "solo 1 WAV")
            else:
                mostrar(f"USB: {cortar(primero['name'], 15)}", "", f"WAVs: {cantidad}", "", "Debe contener", "solo 1 WAV")

            time.sleep(2)
            continue

        # =================================================
        # CASO 4: USB CORRECTO
        # =================================================
        archivo = resultado["archivo"]
        usb = resultado["usb"]
        nombre_usb = usb["name"]
        ruta_usb = usb["disk"].get("path")

        if not ruta_usb:
            raise RuntimeError("No se pudo determinar la ruta del USB")

        stat = archivo.stat()
        tamano = stat.st_size
        canales = canales_wav(archivo)

        # Muestra la información 5s antes de copiar
        for segundos in range(ESPERA_ANTES_COPIA, 0, -1):
            if not archivo.exists():
                raise FileNotFoundError("USB retirado antes de copiar")

            mostrar(
                f"USB: {cortar(nombre_usb, 15)}",
                cortar(archivo.name, 20),
                f"SIZE: {formato_tamano(tamano)}",
                f"CHANNELS: {canales}",
                "",
                f"COPIA EN: {segundos}s"
            )
            time.sleep(1)

        # Ejecuta la copia
        copiar_archivo(archivo, DESTINO_FILE, nombre_usb, canales)

        mostrar("Copia completa", "", "archivoAReproducir", ".wav", f"CH: {canales}", formato_tamano(tamano))
        time.sleep(2)

        # Desmonta y espera el retiro físico
        expulsar_usb(ruta_usb)
        esperar_retiro_usb(ruta_usb)

        # Carga el script de control (info.py) tras retirar la USB
        mostrar("USB Retirada", "", "Cargando", "", "", "")
        time.sleep(1.5)
        ejecutar_info_script()

    except KeyboardInterrupt:
        device.clear()
        print("\nPrograma detenido.")
        break
    except Exception as error:
        print(f"[ERROR] {error}")
        mostrar("ERROR", "", cortar(error, 20), "", "Revise terminal", "")
        time.sleep(2)
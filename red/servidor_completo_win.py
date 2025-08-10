import socket
import json
import threading
import os
import csv
import re
from datetime import datetime

PUERTO_TCP = 5555
PUERTO_UDP = 5556
BUFFER_SIZE = 4096
usuarios_conectados = {}
BASE_DIR = os.path.dirname(os.path.abspath(__file__))


# ------------------- UTILIDADES -------------------

def obtener_ip_local():
    """Obtiene la IP local real."""
    s = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    try:
        s.connect(("8.8.8.8", 80))
        return s.getsockname()[0]
    except:
        return "127.0.0.1"
    finally:
        s.close()


def _safe_filename_from_user(user: str) -> str:
    """Convierte el nombre de usuario en un nombre de archivo seguro."""
    if not user or user.strip().lower() in ("n/a", "none"):
        user = "desconocido"
    name = user.strip()
    name = re.sub(r'[<>:"/\\|?*\n\r\t]+', "_", name)
    if not name:
        name = "usuario"
    return f"{name}.csv"


def guardar_ip_en_csv(usuario: str, ip: str) -> None:
    """
    Crea/actualiza un CSV llamado <usuario>.csv en el mismo directorio
    y coloca la IP en la celda [0,0].
    """
    try:
        ruta = os.path.join(BASE_DIR, _safe_filename_from_user(usuario))
        filas = []
        if os.path.exists(ruta):
            with open(ruta, "r", encoding="utf-8", newline="") as f:
                filas = list(csv.reader(f))
        if not filas:
            filas = [[""]]
        if not filas[0]:
            filas[0] = [""]
        filas[0][0] = ip
        with open(ruta, "w", encoding="utf-8", newline="") as f:
            writer = csv.writer(f)
            writer.writerows(filas)
        print(f"[CSV] Guardada IP {ip} en {ruta} (celda [0,0])")
    except Exception as e:
        print(f"[CSV] ⚠️ Error al guardar CSV: {e}")


def recv_json_lines(conn):
    """Lee del socket hasta encontrar un \\n y devuelve un dict (JSON por línea)."""
    buf = b""
    while True:
        chunk = conn.recv(BUFFER_SIZE)
        if not chunk:
            if buf.strip():
                try:
                    return json.loads(buf.decode(errors="replace"))
                except Exception as e:
                    raise ConnectionError(f"Cierre sin JSON completo: {e}")
            raise ConnectionError("Conexión cerrada por el cliente")
        buf += chunk
        if b"\n" in buf:
            line, _, _ = buf.partition(b"\n")
            return json.loads(line.decode(errors="replace"))


# ------------------- TCP -------------------

def manejar_tcp():
    with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as servidor:
        servidor.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
        servidor.bind(("0.0.0.0", PUERTO_TCP))
        servidor.listen()
        print(f"[TCP] Servidor escuchando en el puerto {PUERTO_TCP}...\n")

        while True:
            conn, addr = servidor.accept()
            ip_cliente = addr[0]
            with conn:
                try:
                    info = recv_json_lines(conn)
                    hora = datetime.now().strftime('%Y-%m-%d %H:%M:%S')
                    usuario = info.get("usuario", "N/A")
                    sistema = info.get("sistema_operativo")
                    temperatura = info.get("temperatura_C")
                    ram_usada = info.get("ram_usada_MB", 0)
                    ram_total = info.get("ram_total_MB", 0)
                    servicios = info.get("servicios", {})

                    usuarios_conectados[ip_cliente] = {
                        "hora": hora,
                        "usuario": usuario,
                        "OS": sistema,
                        "temperatura": temperatura,
                        "ram_usada_MB": ram_usada,
                        "ram_total_MB": ram_total,
                        "servicios": servicios
                    }

                    # Guardar IP en CSV
                    guardar_ip_en_csv(usuario, ip_cliente)

                    # Mostrar en consola
                    print(f"\n[TCP] Conexión desde {ip_cliente}")
                    print(f"  Hora: {hora}")
                    print(f"  Usuario: {usuario}")
                    print(f"  OS: {sistema}")
                    print(f"  RAM usada: {ram_usada} MB / {ram_total} MB")
                    print(f"  Temp CPU: {temperatura if temperatura else 'N/A'} °C")
                    if servicios:
                        print("  Servicios:")
                        for servicio, estado in servicios.items():
                            simbolo = "[OK]" if estado else "[X]"
                            print(f"    {simbolo} {servicio}")
                    else:
                        print("  No se reportaron servicios.")
                except Exception as e:
                    print(f"[TCP] ⚠️ Error con {ip_cliente}: {e}")


# ------------------- UDP -------------------

def manejar_udp():
    TOKEN_REQUERIDO = os.environ.get("DISCOVERY_TOKEN", None)
    with socket.socket(socket.AF_INET, socket.SOCK_DGRAM) as udp:
        udp.bind(("0.0.0.0", PUERTO_UDP))
        print(f"[UDP] Esperando descubrimientos en el puerto {PUERTO_UDP}...")
        while True:
            try:
                mensaje, addr = udp.recvfrom(1024)
                contenido = json.loads(mensaje.decode(errors="replace"))
                if TOKEN_REQUERIDO and contenido.get("token") != TOKEN_REQUERIDO:
                    continue
                respuesta = json.dumps({"ip": obtener_ip_local(), "tcp_port": PUERTO_TCP})
                udp.sendto(respuesta.encode(), addr)
                print(f"[UDP] Respuesta enviada a {addr[0]}")
            except Exception as e:
                print(f"[UDP] ⚠️ Error: {e}")
                continue


# ------------------- MAIN -------------------

if __name__ == "__main__":
    hilo_tcp = threading.Thread(target=manejar_tcp, daemon=True)
    hilo_udp = threading.Thread(target=manejar_udp, daemon=True)
    hilo_tcp.start()
    hilo_udp.start()
    hilo_tcp.join()
    hilo_udp.join()

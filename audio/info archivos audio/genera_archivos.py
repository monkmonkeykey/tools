from pathlib import Path
import csv
import shutil
import subprocess
from typing import Optional


# ---------------------------------------------------------
# CONFIGURACIÓN
# ---------------------------------------------------------

CARPETA_ORIGEN = Path(
    "/Users/josue/Music/FINALES LA SUITE/Master 19 Julio"
)

ARCHIVO_CSV = CARPETA_ORIGEN / "analisis_lufs.csv"

CARPETA_SALIDA = (
    CARPETA_ORIGEN / "ARCHIVOS_SILENCIOSOS"
)

ARCHIVO_REGISTRO = (
    CARPETA_SALIDA / "registro_generacion.csv"
)


# ---------------------------------------------------------
# CONVERSIONES
# ---------------------------------------------------------

def convertir_a_float(valor) -> Optional[float]:
    if valor is None:
        return None

    texto = str(valor).strip()

    if not texto or texto.lower() == "nan":
        return None

    try:
        return float(texto.replace(",", "."))
    except ValueError:
        return None


def convertir_a_entero(valor) -> Optional[int]:
    numero = convertir_a_float(valor)

    if numero is None:
        return None

    return int(numero)


# ---------------------------------------------------------
# CONFIGURACIÓN DE CANALES
# ---------------------------------------------------------

def obtener_layout_canales(canales: int) -> str:
    """
    Devuelve un channel layout reconocido por FFmpeg.
    """

    layouts = {
        1: "mono",
        2: "stereo",
        3: "2.1",
        4: "quad",
        5: "5.0",
        6: "5.1",
        7: "6.1",
        8: "7.1",
    }

    if canales not in layouts:
        raise ValueError(
            f"No se definió un layout para {canales} canales."
        )

    return layouts[canales]


# ---------------------------------------------------------
# CÓDEC
# ---------------------------------------------------------

def obtener_codec(
    extension: str,
    codec_csv: str,
    profundidad_bits: Optional[int],
) -> str:
    """
    Selecciona el códec de salida.

    Para WAV y AIFF se intenta respetar exactamente
    el códec indicado por ffprobe.
    """

    extension = extension.lower()
    codec_csv = str(codec_csv or "").strip().lower()

    if codec_csv.startswith("pcm_"):
        return codec_csv

    if codec_csv == "flac" or extension == ".flac":
        return "flac"

    if extension == ".mp3":
        return "libmp3lame"

    if extension in {".m4a", ".aac"}:
        return "aac"

    if extension == ".ogg":
        if codec_csv == "opus":
            return "libopus"

        return "libvorbis"

    # Alternativa para archivos WAV cuando no se pudo
    # recuperar el nombre exacto del códec.
    if extension == ".wav":
        mapa_wav = {
            8: "pcm_u8",
            16: "pcm_s16le",
            24: "pcm_s24le",
            32: "pcm_s32le",
            64: "pcm_f64le",
        }

        if profundidad_bits in mapa_wav:
            return mapa_wav[profundidad_bits]

    # Alternativa para AIFF.
    if extension in {".aif", ".aiff"}:
        mapa_aiff = {
            8: "pcm_s8",
            16: "pcm_s16be",
            24: "pcm_s24be",
            32: "pcm_s32be",
        }

        if profundidad_bits in mapa_aiff:
            return mapa_aiff[profundidad_bits]

    raise ValueError(
        f"No se pudo determinar el códec para {extension}."
    )


# ---------------------------------------------------------
# TAMAÑO OBJETIVO
# ---------------------------------------------------------

def obtener_tamano_objetivo(
    archivo_original: Path,
    fila: dict,
) -> int:
    """
    Usa el tamaño real del archivo original.

    Si el original no está disponible, utiliza Peso MB
    del CSV. Esa segunda opción será menos exacta porque
    el CSV contiene un valor redondeado.
    """

    if archivo_original.exists():
        return archivo_original.stat().st_size

    peso_mb = convertir_a_float(
        fila.get("Peso MB")
    )

    if peso_mb is None:
        raise ValueError(
            "No está disponible el archivo original "
            "ni la columna Peso MB."
        )

    return round(peso_mb * 1_000_000)


# ---------------------------------------------------------
# GENERACIÓN CON FFMPEG
# ---------------------------------------------------------

def generar_silencio(
    archivo_salida: Path,
    duracion: float,
    sample_rate: int,
    canales: int,
    codec: str,
    bitrate_kbps: Optional[float],
) -> None:
    """
    Genera audio compuesto únicamente por muestras cero.
    """

    layout = obtener_layout_canales(canales)

    comando = [
        "ffmpeg",
        "-y",
        "-hide_banner",
        "-loglevel",
        "error",

        "-f",
        "lavfi",

        "-i",
        (
            f"anullsrc="
            f"r={sample_rate}:"
            f"cl={layout}"
        ),

        "-t",
        f"{duracion:.9f}",

        "-ar",
        str(sample_rate),

        "-ac",
        str(canales),

        "-map_metadata",
        "-1",

        "-fflags",
        "+bitexact",

        "-flags:a",
        "+bitexact",

        "-c:a",
        codec,
    ]

    # Solo se utiliza el bitrate para formatos comprimidos.
    if (
        bitrate_kbps is not None
        and not codec.startswith("pcm_")
        and codec not in {"flac", "alac"}
    ):
        comando.extend([
            "-b:a",
            f"{round(bitrate_kbps)}k",
        ])

    comando.append(str(archivo_salida))

    resultado = subprocess.run(
        comando,
        capture_output=True,
        text=True,
    )

    if resultado.returncode != 0:
        raise RuntimeError(
            resultado.stderr.strip()
            or "FFmpeg no pudo generar el archivo."
        )


# ---------------------------------------------------------
# AJUSTE DE TAMAÑO
# ---------------------------------------------------------

def agregar_chunk_relleno_wav(
    archivo: Path,
    tamano_objetivo: int,
) -> bool:
    """
    Añade un chunk JUNK a un archivo WAV RIFF.

    El chunk no contiene audio y permite alcanzar el
    tamaño solicitado manteniendo un contenedor válido.
    """

    tamano_actual = archivo.stat().st_size
    diferencia = tamano_objetivo - tamano_actual

    if diferencia == 0:
        return True

    if diferencia < 8 or diferencia % 2 != 0:
        return False

    payload = diferencia - 8

    with archivo.open("r+b") as manejador:
        encabezado = manejador.read(12)

        if (
            encabezado[0:4] != b"RIFF"
            or encabezado[8:12] != b"WAVE"
        ):
            return False

        manejador.seek(0, 2)

        manejador.write(b"JUNK")
        manejador.write(
            payload.to_bytes(
                4,
                byteorder="little",
                signed=False,
            )
        )

        manejador.write(b"\x00" * payload)

        # Actualiza el tamaño RIFF.
        manejador.seek(4)

        manejador.write(
            (tamano_objetivo - 8).to_bytes(
                4,
                byteorder="little",
                signed=False,
            )
        )

    return archivo.stat().st_size == tamano_objetivo


def agregar_chunk_relleno_aiff(
    archivo: Path,
    tamano_objetivo: int,
) -> bool:
    """
    Añade un chunk ANNO a un archivo AIFF.
    """

    tamano_actual = archivo.stat().st_size
    diferencia = tamano_objetivo - tamano_actual

    if diferencia == 0:
        return True

    if diferencia < 8 or diferencia % 2 != 0:
        return False

    payload = diferencia - 8

    with archivo.open("r+b") as manejador:
        encabezado = manejador.read(12)

        if encabezado[0:4] != b"FORM":
            return False

        manejador.seek(0, 2)

        manejador.write(b"ANNO")
        manejador.write(
            payload.to_bytes(
                4,
                byteorder="big",
                signed=False,
            )
        )

        manejador.write(b"\x00" * payload)

        # Actualiza el tamaño FORM.
        manejador.seek(4)

        manejador.write(
            (tamano_objetivo - 8).to_bytes(
                4,
                byteorder="big",
                signed=False,
            )
        )

    return archivo.stat().st_size == tamano_objetivo


def rellenar_hasta_tamano(
    archivo: Path,
    tamano_objetivo: int,
) -> None:
    """
    Lleva el archivo al tamaño exacto.

    WAV y AIFF reciben chunks de relleno válidos.
    Otros formatos reciben bytes nulos al final.
    """

    tamano_actual = archivo.stat().st_size

    if tamano_actual > tamano_objetivo:
        raise ValueError(
            "El archivo generado es mayor que el "
            "tamaño objetivo."
        )

    if tamano_actual == tamano_objetivo:
        return

    extension = archivo.suffix.lower()

    if extension == ".wav":
        if agregar_chunk_relleno_wav(
            archivo,
            tamano_objetivo,
        ):
            return

    if extension in {".aif", ".aiff"}:
        if agregar_chunk_relleno_aiff(
            archivo,
            tamano_objetivo,
        ):
            return

    # Recurso alternativo para formatos comprimidos
    # o diferencias demasiado pequeñas.
    diferencia = (
        tamano_objetivo
        - archivo.stat().st_size
    )

    with archivo.open("ab") as manejador:
        manejador.write(b"\x00" * diferencia)


# ---------------------------------------------------------
# CREAR UN ARCHIVO
# ---------------------------------------------------------

def crear_archivo_silencioso(
    fila: dict,
) -> dict:
    nombre = str(
        fila.get("Archivo", "")
    ).strip()

    if not nombre:
        raise ValueError(
            "La fila no contiene un nombre de archivo."
        )

    original = CARPETA_ORIGEN / nombre
    salida = CARPETA_SALIDA / nombre

    salida.parent.mkdir(
        parents=True,
        exist_ok=True,
    )

    extension = salida.suffix.lower()

    sample_rate = convertir_a_entero(
        fila.get("Frecuencia de muestreo Hz")
    )

    canales = convertir_a_entero(
        fila.get("Canales")
    )

    profundidad = convertir_a_entero(
        fila.get("Profundidad de bits")
    )

    duracion_original = convertir_a_float(
        fila.get("Duración segundos")
    )

    bitrate = convertir_a_float(
        fila.get("Bitrate kbps")
    )

    codec = obtener_codec(
        extension=extension,
        codec_csv=fila.get("Códec", ""),
        profundidad_bits=profundidad,
    )

    if sample_rate is None:
        raise ValueError(
            "Falta la frecuencia de muestreo."
        )

    if canales is None:
        raise ValueError(
            "Falta el número de canales."
        )

    if duracion_original is None:
        raise ValueError(
            "Falta la duración."
        )

    tamano_objetivo = obtener_tamano_objetivo(
        archivo_original=original,
        fila=fila,
    )

    temporal = salida.with_name(
        salida.stem
        + ".__temporal__"
        + salida.suffix
    )

    if temporal.exists():
        temporal.unlink()

    bytes_por_segundo = None

    if (
        profundidad is not None
        and codec.startswith("pcm_")
    ):
        bytes_por_segundo = (
            sample_rate
            * canales
            * profundidad
            / 8
        )

    duracion_generacion = duracion_original

    # Puede ser necesario reducir unos cuantos samples
    # para dejar espacio para el chunk de relleno.
    for _ in range(12):
        if temporal.exists():
            temporal.unlink()

        generar_silencio(
            archivo_salida=temporal,
            duracion=duracion_generacion,
            sample_rate=sample_rate,
            canales=canales,
            codec=codec,
            bitrate_kbps=bitrate,
        )

        tamano_generado = temporal.stat().st_size
        diferencia = tamano_objetivo - tamano_generado

        # Se requiere una diferencia mínima de 8 bytes
        # para añadir un chunk WAV/AIFF.
        necesita_mas_espacio = (
            extension in {".wav", ".aif", ".aiff"}
            and 0 < diferencia < 8
        )

        if (
            tamano_generado <= tamano_objetivo
            and not necesita_mas_espacio
        ):
            break

        if bytes_por_segundo:
            exceso = max(
                tamano_generado - tamano_objetivo,
                8 - diferencia,
                1,
            )

            reduccion = (
                exceso / bytes_por_segundo
                + 2 / sample_rate
            )

        else:
            proporcion = (
                tamano_objetivo
                / tamano_generado
            )

            nueva_duracion = (
                duracion_generacion
                * proporcion
                * 0.995
            )

            reduccion = (
                duracion_generacion
                - nueva_duracion
            )

        duracion_generacion = max(
            0.001,
            duracion_generacion - reduccion,
        )

    if temporal.stat().st_size > tamano_objetivo:
        temporal.unlink(missing_ok=True)

        raise RuntimeError(
            "No fue posible generar un archivo menor "
            "o igual al tamaño objetivo."
        )

    rellenar_hasta_tamano(
        archivo=temporal,
        tamano_objetivo=tamano_objetivo,
    )

    if salida.exists():
        salida.unlink()

    temporal.rename(salida)

    tamano_final = salida.stat().st_size

    return {
        "Archivo": nombre,
        "Códec": codec,
        "Canales": canales,
        "Frecuencia Hz": sample_rate,
        "Profundidad bits": profundidad or "",
        "Duración original": round(
            duracion_original,
            6,
        ),
        "Duración generada": round(
            duracion_generacion,
            6,
        ),
        "Tamaño objetivo bytes": tamano_objetivo,
        "Tamaño final bytes": tamano_final,
        "Coincide tamaño": (
            "Sí"
            if tamano_final == tamano_objetivo
            else "No"
        ),
        "Estado": "Correcto",
    }


# ---------------------------------------------------------
# PROGRAMA PRINCIPAL
# ---------------------------------------------------------

def main() -> None:
    if shutil.which("ffmpeg") is None:
        raise SystemExit(
            "No se encontró FFmpeg.\n"
            "Instálalo con: brew install ffmpeg"
        )

    if not ARCHIVO_CSV.exists():
        raise SystemExit(
            f"No se encontró el CSV:\n"
            f"{ARCHIVO_CSV}"
        )

    CARPETA_SALIDA.mkdir(
        parents=True,
        exist_ok=True,
    )

    resultados = []

    with ARCHIVO_CSV.open(
        "r",
        encoding="utf-8-sig",
        newline="",
    ) as archivo:
        lector = csv.DictReader(archivo)
        filas = list(lector)

    total = len(filas)

    for indice, fila in enumerate(
        filas,
        start=1,
    ):
        nombre = fila.get(
            "Archivo",
            "Sin nombre",
        )

        print(
            f"[{indice}/{total}] "
            f"Creando: {nombre}"
        )

        try:
            resultado = crear_archivo_silencioso(
                fila
            )

        except Exception as error:
            resultado = {
                "Archivo": nombre,
                "Códec": fila.get("Códec", ""),
                "Canales": fila.get("Canales", ""),
                "Frecuencia Hz": fila.get(
                    "Frecuencia de muestreo Hz",
                    "",
                ),
                "Profundidad bits": fila.get(
                    "Profundidad de bits",
                    "",
                ),
                "Duración original": fila.get(
                    "Duración segundos",
                    "",
                ),
                "Duración generada": "",
                "Tamaño objetivo bytes": "",
                "Tamaño final bytes": "",
                "Coincide tamaño": "No",
                "Estado": str(error),
            }

        resultados.append(resultado)

    columnas = [
        "Archivo",
        "Códec",
        "Canales",
        "Frecuencia Hz",
        "Profundidad bits",
        "Duración original",
        "Duración generada",
        "Tamaño objetivo bytes",
        "Tamaño final bytes",
        "Coincide tamaño",
        "Estado",
    ]

    with ARCHIVO_REGISTRO.open(
        "w",
        encoding="utf-8-sig",
        newline="",
    ) as archivo:
        escritor = csv.DictWriter(
            archivo,
            fieldnames=columnas,
        )

        escritor.writeheader()
        escritor.writerows(resultados)

    print("\nProceso terminado.")
    print(
        f"Archivos silenciosos:\n"
        f"{CARPETA_SALIDA}"
    )
    print(
        f"\nRegistro:\n"
        f"{ARCHIVO_REGISTRO}"
    )


if __name__ == "__main__":
    main()
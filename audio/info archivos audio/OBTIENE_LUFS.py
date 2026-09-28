from pathlib import Path
import csv
import json
import math
import shutil
import subprocess
from typing import Optional, Union


# ---------------------------------------------------------
# CONFIGURACIÓN
# ---------------------------------------------------------

CARPETA_AUDIO = Path(
    "/Users/josue/Music/REAPER LA SUITE"
)

ARCHIVO_RESULTADOS = CARPETA_AUDIO / "analisis_lufs.csv"

EXTENSIONES_AUDIO = {
    ".wav",
    ".aif",
    ".aiff",
    ".flac",
    ".mp3",
    ".m4a",
    ".aac",
    ".ogg",
}


# ---------------------------------------------------------
# FUNCIONES GENERALES
# ---------------------------------------------------------

def percentil(
    valores: list[float],
    porcentaje: float,
) -> Optional[float]:
    """
    Calcula un percentil mediante interpolación lineal.
    """
    if not valores:
        return None

    valores_ordenados = sorted(valores)

    if len(valores_ordenados) == 1:
        return valores_ordenados[0]

    posicion = (len(valores_ordenados) - 1) * porcentaje
    inferior = math.floor(posicion)
    superior = math.ceil(posicion)

    if inferior == superior:
        return valores_ordenados[inferior]

    fraccion = posicion - inferior

    return (
        valores_ordenados[inferior] * (1 - fraccion)
        + valores_ordenados[superior] * fraccion
    )


def convertir_true_peak_a_dbtp(
    valor_lineal: float,
) -> Optional[float]:
    """
    Convierte el valor lineal entregado por FFmpeg a dBTP.
    """
    if valor_lineal <= 0:
        return None

    return 20 * math.log10(valor_lineal)


def convertir_a_float(valor) -> Optional[float]:
    """
    Convierte un valor a float si es posible.
    """
    if valor in (None, "", "N/A"):
        return None

    try:
        return float(valor)
    except (TypeError, ValueError):
        return None


def convertir_a_entero(valor) -> Optional[int]:
    """
    Convierte un valor a entero si es posible.
    """
    if valor in (None, "", "N/A"):
        return None

    try:
        numero = int(valor)

        if numero <= 0:
            return None

        return numero

    except (TypeError, ValueError):
        return None


def redondear(valor, decimales: int = 2):
    """
    Redondea únicamente valores flotantes.
    """
    if isinstance(valor, float):
        return round(valor, decimales)

    return valor


# ---------------------------------------------------------
# PROFUNDIDAD DE BITS
# ---------------------------------------------------------

def detectar_profundidad_bits(
    stream: dict,
) -> Union[int, str]:
    """
    Detecta la profundidad de bits del audio.

    Primero consulta:
    - bits_per_raw_sample
    - bits_per_sample

    Si FFprobe no entrega esos campos, intenta inferirla
    a partir del nombre del códec PCM.
    """

    for campo in (
        "bits_per_raw_sample",
        "bits_per_sample",
    ):
        bits = convertir_a_entero(stream.get(campo))

        if bits is not None:
            return bits

    codec = str(
        stream.get("codec_name", "")
    ).lower()

    # Códecs con pérdida: no tienen una profundidad PCM
    # fija equivalente a 16, 24 o 32 bits.
    codecs_con_perdida = {
        "mp3",
        "aac",
        "vorbis",
        "opus",
        "ac3",
        "eac3",
        "wmav1",
        "wmav2",
    }

    if codec in codecs_con_perdida:
        return "No aplica"

    # Inferencia para formatos PCM.
    if codec.startswith("pcm_"):

        if "s8" in codec or "u8" in codec:
            return 8

        if "s16" in codec or "u16" in codec:
            return 16

        if "s24" in codec or "u24" in codec:
            return 24

        if (
            "s32" in codec
            or "u32" in codec
            or "f32" in codec
        ):
            return 32

        if (
            "s64" in codec
            or "u64" in codec
            or "f64" in codec
        ):
            return 64

    return "No disponible"


# ---------------------------------------------------------
# METADATOS DEL ARCHIVO
# ---------------------------------------------------------

def obtener_metadatos_audio(
    archivo: Path,
) -> dict:
    """
    Obtiene metadatos técnicos con ffprobe.
    """

    comando = [
        "ffprobe",
        "-v",
        "error",

        # Selecciona únicamente el primer stream de audio.
        "-select_streams",
        "a:0",

        # Campos que necesitamos.
        "-show_entries",
        (
            "stream="
            "codec_name,"
            "codec_long_name,"
            "sample_fmt,"
            "sample_rate,"
            "channels,"
            "channel_layout,"
            "bits_per_sample,"
            "bits_per_raw_sample,"
            "bit_rate:"
            "format="
            "format_name,"
            "duration,"
            "size,"
            "bit_rate"
        ),

        "-of",
        "json",

        str(archivo),
    ]

    resultado = subprocess.run(
        comando,
        capture_output=True,
        text=True,
    )

    if resultado.returncode != 0:
        raise RuntimeError(
            resultado.stderr.strip()
            or "FFprobe no pudo leer los metadatos."
        )

    try:
        datos = json.loads(resultado.stdout)
    except json.JSONDecodeError as error:
        raise RuntimeError(
            "FFprobe devolvió información JSON inválida."
        ) from error

    streams = datos.get("streams", [])

    if not streams:
        raise RuntimeError(
            "No se encontró un stream de audio."
        )

    stream = streams[0]
    formato = datos.get("format", {})

    duracion = convertir_a_float(
        formato.get("duration")
    )

    sample_rate = convertir_a_entero(
        stream.get("sample_rate")
    )

    canales = convertir_a_entero(
        stream.get("channels")
    )

    # Usa primero el bitrate del stream.
    # Si no está disponible, utiliza el del contenedor.
    bitrate = convertir_a_float(
        stream.get("bit_rate")
    )

    if bitrate is None:
        bitrate = convertir_a_float(
            formato.get("bit_rate")
        )

    bitrate_kbps = (
        bitrate / 1000
        if bitrate is not None
        else None
    )

    # Se utiliza MB decimal:
    # 1 MB = 1,000,000 bytes.
    peso_mb = archivo.stat().st_size / 1_000_000

    return {
        "Formato": archivo.suffix.lower(),
        "Códec": stream.get(
            "codec_name",
            "No disponible",
        ),
        "Descripción del códec": stream.get(
            "codec_long_name",
            "No disponible",
        ),
        "Profundidad de bits": detectar_profundidad_bits(
            stream
        ),
        "Formato de muestra": stream.get(
            "sample_fmt",
            "No disponible",
        ),
        "Frecuencia de muestreo Hz": sample_rate,
        "Canales": canales,
        "Configuración de canales": stream.get(
            "channel_layout",
            "No disponible",
        ),
        "Bitrate kbps": bitrate_kbps,
        "Peso MB": peso_mb,
        "Duración segundos": duracion,
    }


# ---------------------------------------------------------
# ANÁLISIS DE SONORIDAD
# ---------------------------------------------------------

def analizar_audio(archivo: Path) -> dict:
    """
    Analiza una pista con el medidor EBU R128 de FFmpeg.
    """

    metadatos = obtener_metadatos_audio(archivo)

    comando = [
        "ffmpeg",
        "-hide_banner",
        "-nostats",
        "-v",
        "error",
        "-i",
        str(archivo),
        "-map",
        "0:a:0",
        "-af",
        (
            "ebur128=metadata=1:peak=true,"
            "ametadata=print:file=-"
        ),
        "-f",
        "null",
        "-",
    ]

    resultado = subprocess.run(
        comando,
        capture_output=True,
        text=True,
    )

    if resultado.returncode != 0:
        raise RuntimeError(
            resultado.stderr.strip()
            or "FFmpeg no pudo analizar el archivo."
        )

    valores_m: list[float] = []
    valores_s: list[float] = []
    valores_i: list[float] = []
    valores_lra: list[float] = []
    valores_true_peak: list[float] = []

    claves = {
        "lavfi.r128.M": valores_m,
        "lavfi.r128.S": valores_s,
        "lavfi.r128.I": valores_i,
        "lavfi.r128.LRA": valores_lra,
        "lavfi.r128.true_peak": valores_true_peak,
    }

    for linea in resultado.stdout.splitlines():

        if "=" not in linea:
            continue

        clave, valor_texto = linea.strip().split(
            "=",
            1,
        )

        if clave not in claves:
            continue

        try:
            valor = float(valor_texto)
        except ValueError:
            continue

        claves[clave].append(valor)

    # Elimina valores iniciales inválidos cercanos
    # a -120 LUFS.
    valores_m_validos = [
        valor
        for valor in valores_m
        if valor > -100
    ]

    valores_s_validos = [
        valor
        for valor in valores_s
        if valor > -100
    ]

    # El último valor corresponde al resultado
    # integrado final.
    lufs_i = (
        valores_i[-1]
        if valores_i
        else None
    )

    lra = (
        valores_lra[-1]
        if valores_lra
        else None
    )

    true_peak_lineal = (
        max(valores_true_peak)
        if valores_true_peak
        else None
    )

    true_peak_dbtp = (
        convertir_true_peak_a_dbtp(
            true_peak_lineal
        )
        if true_peak_lineal is not None
        else None
    )

    return {
        "Archivo": archivo.name,

        "Interprete": str(
            archivo.parent.relative_to(
                CARPETA_AUDIO
            )
        ),

        **metadatos,

        "LUFS-I": lufs_i,

        "LUFS-M máximo": (
            max(valores_m_validos)
            if valores_m_validos
            else None
        ),

        "LUFS-M percentil 95": percentil(
            valores_m_validos,
            0.95,
        ),

        "LUFS-S máximo": (
            max(valores_s_validos)
            if valores_s_validos
            else None
        ),

        "LUFS-S percentil 95": percentil(
            valores_s_validos,
            0.95,
        ),

        "LRA": lra,

        "True Peak dBTP": true_peak_dbtp,
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

    if shutil.which("ffprobe") is None:
        raise SystemExit(
            "No se encontró ffprobe.\n"
            "Se instala junto con FFmpeg."
        )

    if not CARPETA_AUDIO.exists():
        raise SystemExit(
            f"No existe la carpeta:\n"
            f"{CARPETA_AUDIO}"
        )

    archivos = sorted(
        archivo
        for archivo in CARPETA_AUDIO.rglob("*")
        if archivo.is_file()
        and archivo.suffix.lower()
        in EXTENSIONES_AUDIO
    )

    if not archivos:
        raise SystemExit(
            "No se encontraron archivos "
            "de audio compatibles."
        )

    resultados = []
    total = len(archivos)

    for indice, archivo in enumerate(
        archivos,
        start=1,
    ):
        print(
            f"[{indice}/{total}] "
            f"Analizando: {archivo.name}"
        )

        try:
            resultado = analizar_audio(archivo)

            resultado = {
                clave: redondear(valor)
                for clave, valor
                in resultado.items()
            }

            resultado["Error"] = ""
            resultados.append(resultado)

        except Exception as error:
            resultados.append({
                "Archivo": archivo.name,

                "Interprete": str(
                    archivo.parent.relative_to(
                        CARPETA_AUDIO
                    )
                ),

                "Formato": archivo.suffix.lower(),

                "Códec": "",
                "Descripción del códec": "",
                "Profundidad de bits": "",
                "Formato de muestra": "",
                "Frecuencia de muestreo Hz": "",
                "Canales": "",
                "Configuración de canales": "",
                "Bitrate kbps": "",

                "Peso MB": round(
                    archivo.stat().st_size
                    / 1_000_000,
                    2,
                ),

                "Duración segundos": "",

                "LUFS-I": "",
                "LUFS-M máximo": "",
                "LUFS-M percentil 95": "",
                "LUFS-S máximo": "",
                "LUFS-S percentil 95": "",
                "LRA": "",
                "True Peak dBTP": "",

                "Error": str(error),
            })

    columnas = [
        "Archivo",
        "Interprete",

        "Formato",
        "Códec",
        "Descripción del códec",
        "Profundidad de bits",
        "Formato de muestra",
        "Frecuencia de muestreo Hz",
        "Canales",
        "Configuración de canales",
        "Bitrate kbps",
        "Peso MB",
        "Duración segundos",

        "LUFS-I",
        "LUFS-M máximo",
        "LUFS-M percentil 95",
        "LUFS-S máximo",
        "LUFS-S percentil 95",
        "LRA",
        "True Peak dBTP",

        "Error",
    ]

    # utf-8-sig facilita que Excel reconozca
    # correctamente acentos y caracteres especiales.
    with ARCHIVO_RESULTADOS.open(
        "w",
        newline="",
        encoding="utf-8-sig",
    ) as archivo_csv:

        escritor = csv.DictWriter(
            archivo_csv,
            fieldnames=columnas,
            extrasaction="ignore",
        )

        escritor.writeheader()
        escritor.writerows(resultados)

    print("\nAnálisis terminado.")

    print(
        f"Resultados guardados en:\n"
        f"{ARCHIVO_RESULTADOS}"
    )


if __name__ == "__main__":
    main()
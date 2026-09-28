from pathlib import Path
import csv
import os
from typing import Optional


# ---------------------------------------------------------
# CONFIGURACIÓN
# ---------------------------------------------------------

CARPETA_ORIGEN = Path(
    "/Users/josue/Music/FINALES LA SUITE/Master 19 Julio"
)

ARCHIVO_CSV = CARPETA_ORIGEN / "analisis_lufs.csv"

CARPETA_SALIDA = CARPETA_ORIGEN / "MASTERS"

ARCHIVO_REGISTRO = (
    CARPETA_SALIDA / "registro_archivos_masters.csv"
)

# Cantidad de bytes escritos en cada operación.
# 1 MB por bloque evita cargar archivos completos en memoria.
TAMANO_BLOQUE = 1024 * 1024

# True:
# genera contenido aleatorio y claramente inválido.
#
# False:
# genera contenido repetitivo, más rápido y también inválido.
USAR_DATOS_ALEATORIOS = True


# ---------------------------------------------------------
# CONVERSIONES
# ---------------------------------------------------------

def convertir_a_float(valor) -> Optional[float]:
    if valor is None:
        return None

    texto = str(valor).strip()

    if not texto:
        return None

    try:
        return float(texto.replace(",", "."))
    except ValueError:
        return None


def limpiar_subcarpeta(valor: str) -> Path:
    """
    Convierte la columna Subcarpeta en una ruta segura.
    """

    texto = str(valor or "").strip()

    if texto in {"", ".", "./"}:
        return Path()

    ruta = Path(texto)

    # Evita que una ruta absoluta o con ".." escriba
    # fuera de la carpeta de salida.
    partes_seguras = [
        parte
        for parte in ruta.parts
        if parte not in {"", ".", "..", "/"}
    ]

    return Path(*partes_seguras)


# ---------------------------------------------------------
# LOCALIZAR EL ARCHIVO ORIGINAL
# ---------------------------------------------------------

def localizar_original(
    nombre: str,
    subcarpeta: Path,
) -> Optional[Path]:
    """
    Busca primero respetando la subcarpeta del CSV.

    Si no se encuentra, busca por nombre dentro de toda
    la carpeta de origen.
    """

    candidato = CARPETA_ORIGEN / subcarpeta / nombre

    if candidato.is_file():
        return candidato

    coincidencias = [
        archivo
        for archivo in CARPETA_ORIGEN.rglob(nombre)
        if archivo.is_file()
        and CARPETA_SALIDA not in archivo.parents
    ]

    if len(coincidencias) == 1:
        return coincidencias[0]

    return None


# ---------------------------------------------------------
# TAMAÑO OBJETIVO
# ---------------------------------------------------------

def obtener_tamano_objetivo(
    fila: dict,
    original: Optional[Path],
) -> tuple[int, str]:
    """
    Devuelve el tamaño objetivo en bytes.

    Prioridad:
    1. Tamaño real del archivo original.
    2. Columna Peso bytes, si existiera.
    3. Columna Peso MB del CSV.
    """

    if original is not None:
        return (
            original.stat().st_size,
            "Archivo original",
        )

    peso_bytes = convertir_a_float(
        fila.get("Peso bytes")
    )

    if peso_bytes is not None:
        return (
            round(peso_bytes),
            "Peso bytes del CSV",
        )

    peso_mb = convertir_a_float(
        fila.get("Peso MB")
    )

    if peso_mb is None:
        raise ValueError(
            "No se encontró el archivo original ni un peso "
            "válido en el CSV."
        )

    # El script anterior calculaba MB decimal:
    # 1 MB = 1,000,000 bytes.
    return (
        round(peso_mb * 1_000_000),
        "Peso MB del CSV",
    )


# ---------------------------------------------------------
# GENERACIÓN DEL ARCHIVO INVÁLIDO
# ---------------------------------------------------------

def generar_archivo_corrupto(
    destino: Path,
    tamano_bytes: int,
) -> None:
    """
    Crea un archivo deliberadamente inválido con el
    tamaño solicitado.

    No genera encabezados WAV, AIFF, FLAC, MP3, etc.
    """

    if tamano_bytes < 0:
        raise ValueError(
            "El tamaño del archivo no puede ser negativo."
        )

    destino.parent.mkdir(
        parents=True,
        exist_ok=True,
    )

    temporal = destino.with_name(
        destino.name + ".temporal"
    )

    if temporal.exists():
        temporal.unlink()

    bytes_restantes = tamano_bytes

    with temporal.open("wb") as archivo_salida:

        while bytes_restantes > 0:
            tamano_actual = min(
                TAMANO_BLOQUE,
                bytes_restantes,
            )

            if USAR_DATOS_ALEATORIOS:
                bloque = os.urandom(tamano_actual)
            else:
                patron = b"ARCHIVO_DANADO_"

                repeticiones = (
                    tamano_actual // len(patron)
                ) + 1

                bloque = (
                    patron * repeticiones
                )[:tamano_actual]

            archivo_salida.write(bloque)

            bytes_restantes -= tamano_actual

    tamano_generado = temporal.stat().st_size

    if tamano_generado != tamano_bytes:
        temporal.unlink(missing_ok=True)

        raise RuntimeError(
            "El tamaño generado no coincide con el solicitado."
        )

    if destino.exists():
        destino.unlink()

    temporal.rename(destino)


# ---------------------------------------------------------
# PROCESAR UNA FILA
# ---------------------------------------------------------

def procesar_fila(fila: dict) -> dict:
    nombre = str(
        fila.get("Archivo", "")
    ).strip()

    if not nombre:
        raise ValueError(
            "La fila no contiene un nombre de archivo."
        )

    subcarpeta = limpiar_subcarpeta(
        fila.get("Subcarpeta", "")
    )

    original = localizar_original(
        nombre=nombre,
        subcarpeta=subcarpeta,
    )

    tamano_objetivo, fuente_tamano = (
        obtener_tamano_objetivo(
            fila=fila,
            original=original,
        )
    )

    destino = (
        CARPETA_SALIDA
        / subcarpeta
        / nombre
    )

    generar_archivo_corrupto(
        destino=destino,
        tamano_bytes=tamano_objetivo,
    )

    tamano_final = destino.stat().st_size

    return {
        "Archivo": nombre,
        "Subcarpeta": str(subcarpeta),
        "Extensión": destino.suffix.lower(),
        "Tamaño objetivo bytes": tamano_objetivo,
        "Tamaño final bytes": tamano_final,
        "Peso MB": round(
            tamano_final / 1_000_000,
            6,
        ),
        "Fuente del tamaño": fuente_tamano,
        "Original localizado": (
            str(original)
            if original is not None
            else "No"
        ),
        "Coincide tamaño": (
            "Sí"
            if tamano_final == tamano_objetivo
            else "No"
        ),
        "Estado": "Generado",
    }


# ---------------------------------------------------------
# PROGRAMA PRINCIPAL
# ---------------------------------------------------------

def main() -> None:
    if not ARCHIVO_CSV.exists():
        raise SystemExit(
            f"No se encontró el CSV:\n{ARCHIVO_CSV}"
        )

    CARPETA_SALIDA.mkdir(
        parents=True,
        exist_ok=True,
    )

    with ARCHIVO_CSV.open(
        "r",
        encoding="utf-8-sig",
        newline="",
    ) as archivo:
        filas = list(csv.DictReader(archivo))

    if not filas:
        raise SystemExit(
            "El CSV no contiene registros."
        )

    resultados = []
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
            f"Generando archivo inválido: {nombre}"
        )

        try:
            resultado = procesar_fila(fila)

        except Exception as error:
            resultado = {
                "Archivo": nombre,
                "Subcarpeta": fila.get(
                    "Subcarpeta",
                    "",
                ),
                "Extensión": Path(
                    str(nombre)
                ).suffix.lower(),
                "Tamaño objetivo bytes": "",
                "Tamaño final bytes": "",
                "Peso MB": "",
                "Fuente del tamaño": "",
                "Original localizado": "",
                "Coincide tamaño": "No",
                "Estado": f"Error: {error}",
            }

        resultados.append(resultado)

    columnas = [
        "Archivo",
        "Subcarpeta",
        "Extensión",
        "Tamaño objetivo bytes",
        "Tamaño final bytes",
        "Peso MB",
        "Fuente del tamaño",
        "Original localizado",
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
        f"\nArchivos generados en:\n"
        f"{CARPETA_SALIDA}"
    )

    print(
        f"\nRegistro guardado en:\n"
        f"{ARCHIVO_REGISTRO}"
    )


if __name__ == "__main__":
    main()
from pathlib import Path
import shutil
import subprocess


# ---------------------------------------------------------
# CONFIGURACIÓN
# ---------------------------------------------------------

CARPETA = Path(
    "/Users/josue/Music/REAPER LA SUITE"
)

# Formato requerido por SetFile:
# MM/DD/YYYY HH:MM:SS
FECHA = "07/20/2026 16:11:00"

# True: incluye los archivos de todas las subcarpetas.
# False: procesa únicamente los archivos directamente dentro de CARPETA.
INCLUIR_SUBCARPETAS = True


# ---------------------------------------------------------
# FUNCIONES
# ---------------------------------------------------------

def obtener_archivos(carpeta: Path) -> list[Path]:
    elementos = carpeta.rglob("*") if INCLUIR_SUBCARPETAS else carpeta.iterdir()

    return [
        elemento
        for elemento in elementos
        if elemento.is_file() and not elemento.is_symlink()
    ]


def modificar_fechas(archivo: Path) -> bool:
    """
    Modifica la fecha de creación y la fecha de modificación.

    No modifica:
    - El nombre
    - La extensión
    - El contenido
    - El tamaño
    """

    try:
        # Fecha de creación
        subprocess.run(
            [
                "SetFile",
                "-d",
                FECHA,
                str(archivo),
            ],
            check=True,
            capture_output=True,
            text=True,
        )

        # Fecha de modificación
        subprocess.run(
            [
                "SetFile",
                "-m",
                FECHA,
                str(archivo),
            ],
            check=True,
            capture_output=True,
            text=True,
        )

        return True

    except subprocess.CalledProcessError as error:
        mensaje = error.stderr.strip() or str(error)

        print(f"ERROR: {archivo}")
        print(f"       {mensaje}")

        return False

    except OSError as error:
        print(f"ERROR: {archivo}")
        print(f"       {error}")

        return False


# ---------------------------------------------------------
# PROGRAMA PRINCIPAL
# ---------------------------------------------------------

def main():
    if not CARPETA.exists():
        raise FileNotFoundError(
            f"La carpeta no existe:\n{CARPETA}"
        )

    if not CARPETA.is_dir():
        raise NotADirectoryError(
            f"La ruta no corresponde a un directorio:\n{CARPETA}"
        )

    if shutil.which("SetFile") is None:
        raise RuntimeError(
            "No se encontró el comando SetFile.\n\n"
            "Instala las herramientas de línea de comandos de Xcode con:\n"
            "xcode-select --install"
        )

    archivos = obtener_archivos(CARPETA)

    if not archivos:
        print("No se encontraron archivos para procesar.")
        return

    print(f"Directorio: {CARPETA}")
    print(f"Fecha de creación y modificación: {FECHA}")
    print(f"Archivos encontrados: {len(archivos)}")
    print("-" * 70)

    modificados = 0
    errores = 0

    for archivo in archivos:
        if modificar_fechas(archivo):
            modificados += 1
            print(f"MODIFICADO: {archivo}")
        else:
            errores += 1

    print("-" * 70)
    print(f"Archivos modificados correctamente: {modificados}")
    print(f"Archivos con errores: {errores}")


if __name__ == "__main__":
    main()
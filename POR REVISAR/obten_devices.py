import socket
import platform
from datetime import datetime

# Obtener el hostname
hostname = socket.gethostname()

# Obtener IP local (real, no 127.0.0.1)
def get_local_ip():
    try:
        # Crea una conexión UDP "falsa" para obtener la IP local asignada
        with socket.socket(socket.AF_INET, socket.SOCK_DGRAM) as s:
            s.connect(("8.8.8.8", 80))  # Dirección arbitraria para forzar salida
            return s.getsockname()[0]
    except Exception:
        return "No se pudo obtener la IP local"

ip_local = get_local_ip()

# Obtener información del sistema operativo
so_info = platform.platform()

# Fecha y hora actual
fecha_hora = datetime.now().strftime("%Y-%m-%d %H:%M:%S")

# Mostrar resultados
print("Información del sistema:")
print(f"Hostname: {hostname}")
print(f"IP Local: {ip_local}")
print(f"Sistema Operativo: {so_info}")
print(f"Fecha y Hora: {fecha_hora}")

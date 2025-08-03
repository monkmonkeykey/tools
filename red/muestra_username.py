import socket
import getpass
import psutil
import time
import subprocess
import json

SERVIDOR_IP = '192.168.15.4'  # IP donde corre obtiene_usernames.py
PUERTO = 5555

def obtener_datos():
    usuario = getpass.getuser()
    
    # Temperatura (si está disponible)
    temperaturas = psutil.sensors_temperatures()
    cpu_temp = None
    if 'cpu-thermal' in temperaturas:
        cpu_temp = temperaturas['cpu-thermal'][0].current
    elif 'coretemp' in temperaturas:
        cpu_temp = temperaturas['coretemp'][0].current

    # RAM
    memoria = psutil.virtual_memory()
    ram_usada = memoria.used // (1024 * 1024)
    ram_total = memoria.total // (1024 * 1024)

    # Estado del servicio
    try:
        estado_servicio = subprocess.run(
            ["systemctl", "is-active", "--quiet", "jacktrip.service"],
            check=False
        )
        servicio_activo = estado_servicio.returncode == 0
    except Exception:
        servicio_activo = None

    return {
        "usuario": usuario,
        "temperatura": cpu_temp,
        "ram_usada_MB": ram_usada,
        "ram_total_MB": ram_total,
        "jacktrip_activo": servicio_activo
    }

def enviar_datos():
    while True:
        datos = obtener_datos()
        mensaje = json.dumps(datos).encode()

        try:
            with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
                s.connect((SERVIDOR_IP, PUERTO))
                s.sendall(mensaje)
                print("✅ Datos enviados:", datos)
        except Exception as e:
            print("❌ Error al enviar datos:", e)

        time.sleep(10)  # Esperar 10 segundos entre envíos

if __name__ == "__main__":
    enviar_datos()

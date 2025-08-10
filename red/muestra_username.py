# corre_servicio.py
import socket
import getpass
import psutil
import time
import subprocess
import json
import platform

PUERTO_TCP = 5555
PUERTO_UDP = 5556
TIEMPO_ESPERA = 10  # segundos entre envíos

def obtener_ip_local():
    try:
        s = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
        s.connect(("8.8.8.8", 80))
        ip = s.getsockname()[0]
        s.close()
        return ip
    except Exception as e:
        print("No se pudo obtener IP local:", e)
        return "desconocida"

def obtener_temperatura():
    try:
        temps = psutil.sensors_temperatures()
        if not temps:
            return None
        for sensor_name, entradas in temps.items():
            for entrada in entradas:
                if entrada.current:
                    return entrada.current
    except:
        return None
    return None

def obtener_datos():
    usuario = getpass.getuser()
    hostname = socket.gethostname() or platform.node()
    sistema = platform.system()
    ip_local = obtener_ip_local()
    temperatura = obtener_temperatura()

    memoria = psutil.virtual_memory()
    ram_usada = memoria.used // (1024 * 1024)
    ram_total = memoria.total // (1024 * 1024)

    jacktrip_activo = None
    if sistema == "Linux":
        try:
            estado = subprocess.run(
                ["systemctl", "is-active", "--quiet", "jacktrip.service"],
                check=False
            )
            jacktrip_activo = estado.returncode == 0
        except:
            jacktrip_activo = None

    return {
        "usuario": usuario,
        "hostname": hostname,
        "sistema_operativo": sistema,
        "ip_local": ip_local,
        "temperatura_C": temperatura,
        "ram_usada_MB": ram_usada,
        "ram_total_MB": ram_total,
        "servicios": {
            "jacktrip": jacktrip_activo
        }
    }

def descubrir_servidor(usuario, hostname):
    mensaje = json.dumps({"usuario": usuario, "hostname": hostname})
    with socket.socket(socket.AF_INET, socket.SOCK_DGRAM) as udp:
        udp.setsockopt(socket.SOL_SOCKET, socket.SO_BROADCAST, 1)
        udp.settimeout(5)
        print(f"Enviando descubrimiento UDP desde {obtener_ip_local()}...")
        try:
            udp.sendto(mensaje.encode(), ("<broadcast>", PUERTO_UDP))
            respuesta, addr = udp.recvfrom(1024)
            info = json.loads(respuesta.decode())
            print(f"Respuesta del servidor recibida desde {addr[0]}")
            return info["ip"]
        except Exception as e:
            print(f"Error en descubrimiento UDP: {e}")
            return None

def enviar_datos():
    usuario = getpass.getuser()
    hostname = socket.gethostname() or platform.node()
    while True:
        servidor_ip = descubrir_servidor(usuario, hostname)
        if servidor_ip:
            datos = obtener_datos()
            print("\nDatos preparados para enviar:")
            print(json.dumps(datos, indent=2))

            try:
                with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
                    s.connect((servidor_ip, PUERTO_TCP))
                    s.sendall(json.dumps(datos).encode())
                    print(f"Datos enviados correctamente a {servidor_ip}")
            except Exception as e:
                print("Error al enviar datos:", e)
        else:
            print("No se encontró el servidor. Reintentando...")

        time.sleep(TIEMPO_ESPERA)

if __name__ == "__main__":
    enviar_datos()

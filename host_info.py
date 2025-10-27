import subprocess
import socket

def obtener_dispositivos():
    dispositivos = []
    # Ejecuta arp -a para obtener dispositivos conectados
    resultado = subprocess.check_output("arp -a", shell=True).decode()

    for linea in resultado.splitlines():
        partes = linea.split()
        if len(partes) >= 2:
            ip = partes[1].strip("()")
            try:
                hostname = socket.gethostbyaddr(ip)[0]
            except socket.herror:
                hostname = "No disponible"
            dispositivos.append((hostname, ip))
    
    return dispositivos

dispositivos = obtener_dispositivos()
for host, ip in dispositivos:
    print(f"Hostname: {host} - IP: {ip}")

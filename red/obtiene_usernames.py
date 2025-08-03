import socket
import ipaddress
import json
from concurrent.futures import ThreadPoolExecutor

PUERTO = 5555
SUBRED = "192.168.15.0/24"
ARCHIVO_SALIDA = "usuarios_detectados.json"

def escanear_dispositivo(ip):
    ip_str = str(ip)
    s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    s.settimeout(0.5)
    try:
        s.connect((ip_str, PUERTO))
        respuesta = s.recv(1024).decode().strip()
        print(f"{ip_str} respondió: usuario remoto = '{respuesta}'")
        return {"ip": ip_str, "usuario": respuesta}
    except Exception:
        return None
    finally:
        s.close()

def escanear_red(subred):
    red = ipaddress.ip_network(subred, strict=False)
    print(f"Escaneando red {subred} en el puerto {PUERTO}...\n")
    ips = list(red.hosts())
    resultados = []

    with ThreadPoolExecutor(max_workers=50) as executor:
        for resultado in executor.map(escanear_dispositivo, ips):
            if resultado:
                resultados.append(resultado)

    if not resultados:
        print("\n❌ No se detectaron dispositivos que respondan en ese puerto.")
    else:
        print(f"\n✅ Dispositivos detectados:")
        for r in resultados:
            print(f" - {r['ip']} -> usuario: {r['usuario']}")

        # Guardar resultados en JSON
        with open(ARCHIVO_SALIDA, "w") as f:
            json.dump(resultados, f, indent=2)
        print(f"\n💾 Resultados guardados en: {ARCHIVO_SALIDA}")

if __name__ == "__main__":
    escanear_red(SUBRED)

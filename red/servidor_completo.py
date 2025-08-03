import socket
import json
import threading
import getpass
from datetime import datetime

PUERTO_TCP = 5555
PUERTO_UDP = 5556
BUFFER_SIZE = 4096
usuarios_conectados = {}

# 🔧 Función confiable para obtener la IP local real
def obtener_ip_local():
    s = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    try:
        s.connect(("8.8.8.8", 80))
        return s.getsockname()[0]
    except:
        return "127.0.0.1"
    finally:
        s.close()

# 🧠 Maneja conexiones TCP para recibir datos del cliente
def manejar_tcp():
    with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as servidor:
        servidor.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
        servidor.bind(('', PUERTO_TCP))
        servidor.listen()
        print(f"🟢 Servidor TCP escuchando en el puerto {PUERTO_TCP}...\n")

        while True:
            conn, addr = servidor.accept()
            with conn:
                try:
                    datos = conn.recv(BUFFER_SIZE).decode().strip()
                    if not datos:
                        print(f"⚠️ Se recibió una cadena vacía desde {addr[0]}")
                        continue

                    info = json.loads(datos)

                    ip = addr[0]
                    hora = datetime.now().strftime('%Y-%m-%d %H:%M:%S')
                    usuario = info.get("usuario", "N/A")
                    sistema = info.get("sistema_operativo")
                    temperatura = info.get("temperatura_C")
                    ram_usada = info.get("ram_usada_MB", 0)
                    ram_total = info.get("ram_total_MB", 0)

                    servicios = info.get("servicios", {})

                    usuarios_conectados[ip] = {
                        "hora": hora,
                        "usuario": usuario,
                        "OS": sistema,
                        "temperatura": temperatura,
                        "ram_usada_MB": ram_usada,
                        "ram_total_MB": ram_total,
                        "servicios": servicios
                    }

                    print(f"\n🔔 Conexión desde {ip}")
                    print(f"🕒 {hora}")
                    print(f"👤 Usuario: {usuario}")
                    print(f"💻 OS: {sistema}")
                    print(f"💾 RAM usada: {ram_usada} MB / {ram_total} MB")
                    print(f"🌡️ Temperatura CPU: {temperatura if temperatura else 'N/A'} °C")

                    # Mostrar servicios recibidos
                    if servicios:
                        print("🧩 Servicios reportados:")
                        for servicio, estado in servicios.items():
                            simbolo = "✅" if estado else "❌"
                            print(f"  {simbolo} {servicio}")
                    else:
                        print("ℹ️ No se reportaron servicios.")

                except Exception as e:
                    print(f"⚠️ Error al procesar datos desde {addr[0]}: {e}")

# 📡 Maneja solicitudes UDP de descubrimiento
def manejar_udp():
    usuario_local = getpass.getuser()
    with socket.socket(socket.AF_INET, socket.SOCK_DGRAM) as udp:
        udp.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
        udp.bind(('', PUERTO_UDP))
        print(f"🛰️ Servidor UDP esperando descubrimientos en el puerto {PUERTO_UDP}...")

        while True:
            try:
                mensaje, addr = udp.recvfrom(1024)
                contenido = json.loads(mensaje.decode())
                if contenido.get("usuario") == usuario_local:
                    respuesta = json.dumps({"ip": obtener_ip_local()})
                    udp.sendto(respuesta.encode(), addr)
                    print(f"📡 Descubrimiento respondido a {addr[0]}")
            except Exception as e:
                print(f"⚠️ Error en UDP: {e}")
                continue

# 🚀 Ejecuta ambos hilos
if __name__ == "__main__":
    threading.Thread(target=manejar_tcp, daemon=True).start()
    manejar_udp()

import socket
import json
from datetime import datetime

PUERTO = 5555
BUFFER_SIZE = 4096
usuarios_conectados = {}

def iniciar_servidor():
    with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as servidor:
        servidor.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
        servidor.bind(('', PUERTO))
        servidor.listen()
        print(f"🟢 Servidor escuchando en el puerto {PUERTO}...\n")

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
                    estado = info.get("estado_jacktrip", "desconocido")

                    # Almacenar para control
                    usuarios_conectados[ip] = {
                        "hora": hora,
                        "usuario": usuario,
                        "OS": sistema,
                        "temperatura": temperatura,
                        "ram_usada_MB": ram_usada,
                        "ram_total_MB": ram_total,
                        "estado_jacktrip": estado
                    }

                    # Imprimir en consola
                    print(f"\nConexión desde: {ip}")
                    print(f"{hora}")
                    print(f"OS: {sistema}")
                    print(f"Usuario: {usuario}")
                    print(f"Temperatura CPU: {temperatura if temperatura is not None else 'N/A'} °C")
                    print(f"RAM usada: {ram_usada} MB / {ram_total} MB")
                    print(f"JackTrip activo: {'Sí' if estado == 'activo' else 'No'}")

                except json.JSONDecodeError as e:
                    print(f"⚠️ Error al decodificar JSON desde {addr[0]}: {e}")
                except Exception as e:
                    print(f"⚠️ Error general al procesar datos desde {addr[0]}: {e}")

if __name__ == "__main__":
    iniciar_servidor()

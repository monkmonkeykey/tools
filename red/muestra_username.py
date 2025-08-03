import socket
import signal
import sys
import getpass

HOST = "0.0.0.0"
PORT = 5555
usuario = getpass.getuser()

def cerrar_servidor(sig, frame):
    print("\nServidor detenido. Liberando puerto...")
    s.close()
    sys.exit(0)

signal.signal(signal.SIGINT, cerrar_servidor)
signal.signal(signal.SIGTERM, cerrar_servidor)

s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)

s.bind((HOST, PORT))
s.listen()
print(f"Servidor activo en el puerto {PORT} como usuario '{usuario}'")

while True:
    try:
        conn, addr = s.accept()
        with conn:
            print(f"Conexión recibida de {addr}")
            conn.sendall(usuario.encode())
    except Exception as e:
        print(f"Error durante la conexión: {e}")

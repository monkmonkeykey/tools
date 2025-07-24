import threading
import time
import RPi.GPIO as GPIO
from pythonosc import dispatcher, osc_server
import atexit
import signal
import sys

# Desactiva advertencias de GPIO
GPIO.setwarnings(False)
GPIO.setmode(GPIO.BCM)

# Diccionario de solenoides: nombre -> pin GPIO
solenoide_pines = {
    "solenoide_uno": 17,
    "solenoide_dos": 18,
    "solenoide_tres": 27,
    "solenoide_cuatro": 21,
    "solenoide_cinco": 13,
    "solenoide_seis": 19,
    "solenoide_siete": 26,
    "solenoide_ocho": 4
}

# Estado anterior para detección de flanco
estados_anteriores = {nombre: 0.0 for nombre in solenoide_pines}

# Configura todos los pines
for pin in solenoide_pines.values():
    GPIO.setup(pin, GPIO.OUT)
    GPIO.output(pin, GPIO.LOW)

# Función para apagar todos los solenoides de forma segura
def apagar_todos():
    print("Apagando todos los solenoides...")
    for nombre, pin in solenoide_pines.items():
        GPIO.output(pin, GPIO.LOW)
    GPIO.cleanup()

# Registra limpieza para salidas normales y errores
atexit.register(apagar_todos)
signal.signal(signal.SIGTERM, lambda sig, frame: sys.exit(0))
signal.signal(signal.SIGINT, lambda sig, frame: sys.exit(0))

# Función de activación con flanco
def manejar_solenoide(address, *args):
    nombre = address.split("/")[-1]

    if nombre not in solenoide_pines:
        print(f"Solenoide desconocido: {nombre}")
        return

    try:
        valor = float(args[0])
    except (IndexError, ValueError):
        print(f"Valor inválido para {nombre}")
        return

    valor_anterior = estados_anteriores[nombre]

    # Detecta flanco de subida
    if valor_anterior == 0 and valor > 0:
        duracion = valor  # en segundos
        pin = solenoide_pines[nombre]
        print(f"Percute: {nombre} por {duracion:.3f}s (GPIO {pin})")

        GPIO.output(pin, GPIO.HIGH)
        time.sleep(duracion)
        GPIO.output(pin, GPIO.LOW)

    # Actualiza estado
    estados_anteriores[nombre] = valor

# Configura despachador OSC
disp = dispatcher.Dispatcher()
for solenoide in solenoide_pines:
    disp.map(f"/{solenoide}", manejar_solenoide)

# Inicia servidor OSC
ip_escucha = "0.0.0.0"
puerto_escucha = 8000
servidor = osc_server.ThreadingOSCUDPServer((ip_escucha, puerto_escucha), disp)
print(f"Servidor OSC escuchando en {ip_escucha}:{puerto_escucha}")

try:
    servidor.serve_forever()
except Exception as e:
    print(f"Error inesperado: {e}")
finally:
    apagar_todos()

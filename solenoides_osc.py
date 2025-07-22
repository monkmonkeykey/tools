import threading
import time
import RPi.GPIO as GPIO
from pythonosc import dispatcher, osc_server

# Desactiva advertencias de GPIO
GPIO.setwarnings(False)
GPIO.setmode(GPIO.BCM)

# Diccionario de solenoides: nombre -> pin GPIO
solenoide_pines = {
    "manzana": 18,
    "platano": 23,
    "pera": 24,
    "uva": 12,
    "kiwi": 13,
    "mango": 19,
    "melon": 26
}

# Configura los pines como salida
for pin in solenoide_pines.values():
    GPIO.setup(pin, GPIO.OUT)
    GPIO.output(pin, GPIO.LOW)

# Función para manejar mensajes OSC
def manejar_solenoide(address, *args):
    nombre = address.split("/")[-1]  # Extrae nombre del solenoide
    if nombre in solenoide_pines:
        pin = solenoide_pines[nombre]
        try:
            duracion = float(args[0])
            if duracion <= 0:
                print(f"Ignorado: duración no válida ({duracion}) para {nombre}")
                return
        except (IndexError, ValueError):
            print(f"Error: no se recibió un valor válido para {nombre}")
            return

        print(f"Activando solenoide: {nombre} (GPIO {pin}) por {duracion:.3f} segundos")
        GPIO.output(pin, GPIO.HIGH)
        time.sleep(duracion)
        GPIO.output(pin, GPIO.LOW)
    else:
        print(f"Solenoide desconocido: {nombre}")

# Configura el despachador OSC
disp = dispatcher.Dispatcher()

# Mapea las direcciones OSC
for fruta in solenoide_pines:
    disp.map(f"/{fruta}", manejar_solenoide)

# Servidor OSC
ip_escucha = "0.0.0.0"
puerto_escucha = 8000
servidor = osc_server.ThreadingOSCUDPServer((ip_escucha, puerto_escucha), disp)
print(f"Servidor OSC escuchando en {ip_escucha}:{puerto_escucha}")

# Ejecuta el servidor
try:
    servidor.serve_forever()
except KeyboardInterrupt:
    print("Detenido por usuario. Limpiando GPIO.")
    GPIO.cleanup()

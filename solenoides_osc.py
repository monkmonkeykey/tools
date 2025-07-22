import threading
import time
import RPi.GPIO as GPIO
from pythonosc import dispatcher, osc_server

# Desactiva advertencias de GPIO
GPIO.setwarnings(False)
GPIO.setmode(GPIO.BCM)

# Diccionario de solenoides: nombre -> pin GPIO
solenoide_pines = {
    "solenoide_uno": 18,
    "platano": 23,
    "pera": 24,
    "uva": 12,
    "kiwi": 13,
    "mango": 19,
    "melon": 26
}

# Estado anterior de cada solenoide (valor recibido previamente)
estados_anteriores = {nombre: 0.0 for nombre in solenoide_pines}

# Configura pines como salida
for pin in solenoide_pines.values():
    GPIO.setup(pin, GPIO.OUT)
    GPIO.output(pin, GPIO.LOW)

# Función que maneja los mensajes OSC
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

    # Detecta flanco de subida: de 0 a > 0
    if valor_anterior == 0 and valor > 0:
        duracion = valor  # Valor es duración en segundos, ya mapeado desde Max/MSP
        pin = solenoide_pines[nombre]
        print(f"Disparo: {nombre} (GPIO {pin}) por {duracion:.3f} segundos")

        GPIO.output(pin, GPIO.HIGH)
        time.sleep(duracion)
        GPIO.output(pin, GPIO.LOW)

    # Actualiza el valor anterior
    estados_anteriores[nombre] = valor

# Configura el despachador OSC
disp = dispatcher.Dispatcher()
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
    print("Interrumpido. Limpiando GPIO.")
    GPIO.cleanup()

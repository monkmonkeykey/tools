#!/usr/bin/env python3
import asyncio
import json
import os
import shutil
import signal
import socket
import subprocess
import time
import RPi.GPIO as GPIO

from pythonosc.dispatcher import Dispatcher
from pythonosc.osc_server import AsyncIOOSCUDPServer
from pythonosc.udp_client import SimpleUDPClient

# ====== LIBRERÍAS PANTALLA OLED (Luma y PIL) ======
from luma.core.interface.serial import i2c
from luma.core.render import canvas
from luma.oled.device import ssd1306
from PIL import ImageFont

import sys
import os
from pathlib import Path

# =========================================================
# AUTODETECCIÓN Y AUTOACTIVACIÓN DE VENV
# =========================================================
VENV_PYTHON = Path(__file__).parent / "venv" / "bin" / "python3"

if VENV_PYTHON.exists() and Path(sys.executable).resolve() != VENV_PYTHON.resolve():
    print(f"[SISTEMA] Relanzando script dentro del entorno virtual: {VENV_PYTHON}")
    os.execv(str(VENV_PYTHON), [str(VENV_PYTHON)] + sys.argv)
# ====== CONFIGURACIÓN DE ARCHIVO DE PERSISTENCIA ======
SAVE_FILE = "volumes.json"

# ====== CONFIGURACIÓN DE RED Y OSC ======
OSC_BIND_IP   = "0.0.0.0"     # Escucha peticiones de cualquier IP
OSC_PORT      = 8000          # Puerto local donde este script escucha
OSC_TX_IP     = "127.0.0.1"   # IP destino hacia donde enviar datos
OSC_TX_PORT   = 1234          # Puerto donde RNBO escucha

# ====== PINES DEL ENCODER ROTATIVO (HW-040) ======
PIN_CLK   = 17    # Pin CLK
PIN_DT    = 27    # Pin DT
PIN_SW    = 22    # Pin SW (Pulsador)
STEP_SIZE = 0.02  # Sensibilidad de cambio por paso de volumen (2%)

# Muescas del HW-040: Pasos de estado acumulados por clic físico
DETENT_STEPS = 2  
LONG_PRESS_TIME = 2.0  # Segundos para activar pulsación larga

# ====== CONFIGURACIÓN PANTALLA OLED ======
serial = i2c(port=1, address=0x3C)
device = ssd1306(serial)
font = ImageFont.load_default()

# ====== ESTADO GLOBAL ======
volumes = [0.0] * 8
selected_channel = 0  # Canal seleccionado (0 a 7)
current_screen = 0    # 0 = Volúmenes, 1 = Información del Sistema
client_osc: SimpleUDPClient = None

# Tabla de transición de la máquina de estados de cuadratura
ENC_STATES = [
     0,  1, -1,  0,
    -1,  0,  0,  1,
     1,  0,  0, -1,
     0, -1,  1,  0
]

# ---------------------------------------------------------------------
# Funciones de Obtención de Datos del Sistema
# ---------------------------------------------------------------------
def get_network_info():
    """Obtiene la IP local y el nombre de la red (SSID de Wi-Fi o LAN)."""
    ip = "Sin conexion"
    net_name = "Desconectado"
    try:
        s = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
        s.settimeout(0.1)
        s.connect(("8.8.8.8", 80))
        ip = s.getsockname()[0]
        s.close()

        # Intenta obtener el nombre de la red Wi-Fi (SSID) con iwgetid
        try:
            ssid = subprocess.check_output(["iwgetid", "-r"], stderr=subprocess.DEVNULL).decode("utf-8").strip()
            if ssid:
                net_name = ssid
            else:
                net_name = "LAN"
        except Exception:
            net_name = "LAN"
    except Exception:
        pass

    return ip, net_name

def get_cpu_temp():
    """Obtiene la temperatura de la CPU."""
    try:
        with open("/sys/class/thermal/thermal_zone0/temp", "r") as f:
            temp = float(f.read().strip()) / 1000.0
            return f"{temp:.1f}°C"
    except Exception:
        return "N/A"

def get_disk_usage():
    """Obtiene el porcentaje y espacio usado/total en el disco principal."""
    try:
        total, used, free = shutil.disk_usage("/")
        percent = int((used / total) * 100)
        used_gb = used / (1024**3)
        total_gb = total / (1024**3)
        return f"{percent}% ({used_gb:.1f}/{total_gb:.1f}G)"
    except Exception:
        return "N/A"

def get_ram_usage():
    """Obtiene el uso de memoria RAM leyendo /proc/meminfo."""
    try:
        with open("/proc/meminfo", "r") as f:
            lines = f.readlines()
        mem_total = 0
        mem_available = 0
        for line in lines:
            if "MemTotal:" in line:
                mem_total = int(line.split()[1])
            elif "MemAvailable:" in line:
                mem_available = int(line.split()[1])
        if mem_total > 0:
            used = mem_total - mem_available
            percent = int((used / mem_total) * 100)
            return f"{percent}% ({used // 1024}MB)"
    except Exception:
        pass
    return "N/A"

# ---------------------------------------------------------------------
# Funciones de Persistencia (JSON)
# ---------------------------------------------------------------------
def load_volumes():
    global volumes
    if os.path.exists(SAVE_FILE):
        try:
            with open(SAVE_FILE, "r") as f:
                data = json.load(f)
                if isinstance(data, list) and len(data) == 8:
                    volumes = [max(0.0, min(1.0, float(v))) for v in data]
                    print(f"[PERSISTENCIA] Valores cargados desde '{SAVE_FILE}': {volumes}")
                    return
        except Exception as e:
            print(f"[PERSISTENCIA] Error al leer '{SAVE_FILE}': {e}")
    
    volumes = [0.0] * 8
    print("[PERSISTENCIA] No se encontró archivo previo. Inicializado a cero.")

def save_volumes():
    try:
        with open(SAVE_FILE, "w") as f:
            json.dump([round(v, 3) for v in volumes], f, indent=2)
    except Exception as e:
        print(f"[PERSISTENCIA] Error al guardar '{SAVE_FILE}': {e}")

def sync_volumes_to_rnbo():
    if client_osc:
        for i, val in enumerate(volumes):
            client_osc.send_message(f"/vol{i+1}", val)
        client_osc.send_message("/volumes", volumes)
        print("[OSC] Volúmenes iniciales sincronizados con RNBO.")

# ---------------------------------------------------------------------
# Renderizado de la Pantalla OLED
# ---------------------------------------------------------------------
def draw_volume_screen(draw):
    """Pantalla 0: Mezclador de 8 Canales de Volumen con Encabezado."""
    # 1. ENCABEZADO
    draw.rectangle((0, 0, 128, 11), fill="white")
    draw.text((8, 1), "Volumen de canales", fill="black", font=font)

    slot_width = 16
    bar_width = 8
    max_bar_height = 25  # Reajustado para dar espacio al encabezado
    bottom_y = 48

    for i, vol in enumerate(volumes):
        bar_x = (i * slot_width) + 4
        height = int(vol * max_bar_height)
        top_y = bottom_y - height
        val_100 = int(round(vol * 100))
        val_str = str(val_100)

        # 2. VALOR DE VOLUMEN (0 a 100)
        if val_100 == 100:
            text_x = bar_x - 3
        elif val_100 >= 10:
            text_x = bar_x - 1
        else:
            text_x = bar_x + 2

        draw.text((text_x, 13), val_str, fill="white", font=font)

        # 3. BARRA DE VOLUMEN
        if height > 0:
            draw.rectangle((bar_x, top_y, bar_x + bar_width, bottom_y), outline="white", fill="white")
        else:
            draw.line((bar_x, bottom_y, bar_x + bar_width, bottom_y), fill="white")

        # 4. NÚMERO DE CANAL ABAJO
        chan_x = bar_x + 1
        if i == selected_channel:
            draw.rectangle((bar_x - 1, 51, bar_x + bar_width + 1, 63), fill="white")
            draw.text((chan_x, 52), str(i + 1), fill="black", font=font)
        else:
            draw.text((chan_x, 52), str(i + 1), fill="white", font=font)

def draw_system_info_screen(draw):
    """Pantalla 1: Información del Sistema y Red."""
    ip, net_name = get_network_info()
    temp = get_cpu_temp()
    disk = get_disk_usage()
    ram = get_ram_usage()

    # Encabezado
    draw.rectangle((0, 0, 128, 11), fill="white")
    draw.text((8, 1), "Estado del sistema", fill="black", font=font)

    # Filas de Información
    draw.text((0, 16), f"IP: {ip}", fill="white", font=font)
    draw.text((0, 28), f"Red: {net_name[:16]}", fill="white", font=font)
    draw.text((0, 40), f"Temp: {temp}  RAM: {ram.split()[0]}", fill="white", font=font)
    draw.text((0, 52), f"Disco: {disk}", fill="white", font=font)

def update_display():
    """Actualiza la pantalla OLED según la vista activa."""
    with canvas(device) as draw:
        if current_screen == 0:
            draw_volume_screen(draw)
        elif current_screen == 1:
            draw_system_info_screen(draw)

# ---------------------------------------------------------------------
# Lógica del Encoder y Botón
# ---------------------------------------------------------------------
def on_encoder_rotate(direction: int):
    global volumes
    # Solo permite modificar volúmenes si estamos en la Pantalla 0
    if current_screen != 0:
        return

    current_val = volumes[selected_channel]
    new_val = max(0.0, min(1.0, current_val + (direction * STEP_SIZE)))
    
    if new_val != current_val:
        volumes[selected_channel] = round(new_val, 3)
        update_display()
        save_volumes()
        
        if client_osc:
            osc_route = f"/vol{selected_channel + 1}"
            client_osc.send_message(osc_route, volumes[selected_channel])
            print(f"[HW-040] {osc_route} -> {volumes[selected_channel]:.2f}")

def on_button_short_press():
    global selected_channel
    if current_screen == 0:
        selected_channel = (selected_channel + 1) % 8
        print(f"[HW-040] Canal seleccionado: {selected_channel + 1}")
    elif current_screen == 1:
        print("[HW-040] Refrescando información del sistema...")
    update_display()

def toggle_screen():
    global current_screen
    current_screen = 1 if current_screen == 0 else 0
    print(f"[HW-040] Cambio de Pantalla -> Pantalla {current_screen}")
    update_display()

async def hw040_task():
    """Monitorea giros del encoder y detecta pulsaciones cortas/largas."""
    GPIO.setmode(GPIO.BCM)
    GPIO.setup(PIN_CLK, GPIO.IN, pull_up_down=GPIO.PUD_UP)
    GPIO.setup(PIN_DT, GPIO.IN, pull_up_down=GPIO.PUD_UP)
    GPIO.setup(PIN_SW, GPIO.IN, pull_up_down=GPIO.PUD_UP)

    old_state = (GPIO.input(PIN_CLK) << 1) | GPIO.input(PIN_DT)
    accumulator = 0

    sw_pressed_time = None
    long_press_triggered = False

    while True:
        clk = GPIO.input(PIN_CLK)
        dt = GPIO.input(PIN_DT)
        current_state = (clk << 1) | dt

        if current_state != old_state:
            idx = (old_state << 2) | current_state
            delta = ENC_STATES[idx]
            old_state = current_state

            if delta != 0:
                accumulator += delta

                if accumulator >= DETENT_STEPS:
                    on_encoder_rotate(-1)
                    accumulator = 0
                elif accumulator <= -DETENT_STEPS:
                    on_encoder_rotate(1)
                    accumulator = 0

        # Lectura del botón SW (Pulsación corta vs larga de 3s)
        sw_state = GPIO.input(PIN_SW)
        now = time.time()

        if sw_state == 0:  # Botón Presionado (LOW)
            if sw_pressed_time is None:
                sw_pressed_time = now
                long_press_triggered = False
            elif not long_press_triggered and (now - sw_pressed_time) >= LONG_PRESS_TIME:
                long_press_triggered = True
                toggle_screen()
        else:  # Botón Liberado (HIGH)
            if sw_pressed_time is not None:
                duration = now - sw_pressed_time
                if not long_press_triggered and duration > 0.05:  # Debounce 50ms
                    on_button_short_press()
                sw_pressed_time = None
                long_press_triggered = False

        await asyncio.sleep(0.001)

async def auto_refresh_info_task():
    """Refresca automáticamente la pantalla de info de sistema cada segundo."""
    while True:
        if current_screen == 1:
            update_display()
        await asyncio.sleep(1.0)

# ---------------------------------------------------------------------
# Handlers OSC Entrantes
# ---------------------------------------------------------------------
def volume_handler(address: str, *args):
    global volumes
    if not args:
        return

    changed = False

    if address.startswith("/vol") and address[4:].isdigit():
        try:
            ch_num = int(address.replace("/vol", ""))
            ch_idx = ch_num - 1

            if 0 <= ch_idx < 8:
                val = max(0.0, min(1.0, float(args[0])))
                if volumes[ch_idx] != val:
                    volumes[ch_idx] = val
                    changed = True
        except ValueError:
            pass

    elif address == "/volumes" and len(args) == 8:
        new_vols = [max(0.0, min(1.0, float(v))) for v in args]
        if new_vols != volumes:
            volumes = new_vols
            changed = True

    if changed:
        if current_screen == 0:
            update_display()
        save_volumes()

# ---------------------------------------------------------------------
# Inicialización OSC y Loop Principal
# ---------------------------------------------------------------------
async def init_osc():
    global client_osc
    dispatcher = Dispatcher()
    dispatcher.map("/vol*", volume_handler)
    dispatcher.map("/volumes", volume_handler)

    client_osc = SimpleUDPClient(OSC_TX_IP, OSC_TX_PORT)

    loop = asyncio.get_event_loop()
    server = AsyncIOOSCUDPServer((OSC_BIND_IP, OSC_PORT), dispatcher, loop)
    transport, protocol = await server.create_serve_endpoint()

    print("=" * 55)
    print(" Servidor OSC + Monitoreo de Sistema Activo")
    print(f" -> Escuchando OSC en: udp://{OSC_BIND_IP}:{OSC_PORT}")
    print(f" -> Transmitiendo OSC a: udp://{OSC_TX_IP}:{OSC_TX_PORT}")
    print("=" * 55)

    return transport, protocol

async def main():
    load_volumes()
    update_display()

    transport, protocol = await init_osc()
    sync_volumes_to_rnbo()

    encoder_job = asyncio.create_task(hw040_task())
    refresh_job = asyncio.create_task(auto_refresh_info_task())

    stop_event = asyncio.Event()
    def _sig(*_): stop_event.set()

    signal.signal(signal.SIGINT, _sig)
    signal.signal(signal.SIGTERM, _sig)

    await stop_event.wait()

    print("\nCerrando aplicación...")
    encoder_job.cancel()
    refresh_job.cancel()
    transport.close()
    device.clear()
    GPIO.cleanup()

if __name__ == "__main__":
    try:
        asyncio.run(main())
    except KeyboardInterrupt:
        device.clear()
        GPIO.cleanup()
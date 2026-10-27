#!/usr/bin/env python3
"""
Interfaz RNBO en Raspberry Pi: mezclador HW-040, estado y reproduccion OLED.

Pantallas (pulsacion larga >=2 s):
    0 - Volumen: controles de 1 a 8 segun outport RNBO /channels.
    1 - Sistema: red, CPU, RAM, disco, tarjeta y salidas JACK activas.
    2 - Reproduccion: durSeg/seg en mm:ss y barra de progreso.

Conserva los controles OSC locales /vol1 ... /vol8 y /volumes en UDP 8000.
Escucha outports de RNBO a traves de /rnbo/listeners/add.
"""

import asyncio
import json
import math
import os
from pathlib import Path
import re
import shutil
import signal
import socket
import struct
import subprocess
import sys
import time
from urllib.request import urlopen

# Mantener esta deteccion ANTES de importar librerias del entorno virtual.
VENV_PYTHON = Path(__file__).resolve().parent / 'venv' / 'bin' / 'python3'
if VENV_PYTHON.exists() and Path(sys.executable).absolute() != VENV_PYTHON.absolute():
    print(f'[SISTEMA] Relanzando con {VENV_PYTHON}', flush=True)
    os.execv(str(VENV_PYTHON), [str(VENV_PYTHON)] + sys.argv)

import RPi.GPIO as GPIO
from pythonosc.dispatcher import Dispatcher
from pythonosc.osc_server import AsyncIOOSCUDPServer
from pythonosc.udp_client import SimpleUDPClient
from luma.core.interface.serial import i2c
from luma.core.render import canvas
from luma.oled.device import ssd1306
from PIL import ImageFont

# =========================================================
# CONFIGURACION
# =========================================================
SAVE_FILE = Path(__file__).resolve().parent / 'volumes.json'
WAV_FILE = Path('/home/pi/Documents/rnbo/datafiles/audio.wav')

OSC_BIND_IP = '0.0.0.0'
OSC_PORT = 8000                 # Controles de volumen + notificaciones RNBO
OSC_TX_IP = '127.0.0.1'
OSC_TX_PORT = 1234             # OSCQuery Runner
OSC_LISTENER_IP = '127.0.0.1'  # IP publica al Runner (NO 0.0.0.0)
OSC_INSTANCE = 0
OSC_OUT_BASE = f'/rnbo/inst/{OSC_INSTANCE}/messages/out'
RUNNER_HTTP = 'http://127.0.0.1:5678'

# PCB: pines FISICOS 13, 19 y 26 (GPIO BCM 27, 10 y 7).
# Si en tu PCB 13/19/26 son NUMEROS BCM, cambia a 13/19/26.
# GPIO 10 y 7 comparten funciones alternativas SPI: no activar SPI en esos pines.
PIN_CLK = 17         #16          # CLK -> fisico 13
PIN_DT = 27          # 19         # DT  -> fisico 19
PIN_SW = 22           #  26        # SW  -> fisico 26
STEP_SIZE = 0.02
DETENT_STEPS = 2
LONG_PRESS_TIME = 1.5

OLED_ADDR = 0x3C
OLED_WIDTH, OLED_HEIGHT = 128, 64
DISPLAY_FPS = 8               # Limite maximo de refresco, no un refresco fijo
SYS_REFRESH_SECONDS = 5.0     # Telemetria local
AUDIO_REFRESH_SECONDS = 20.0  # Seleccion de tarjeta y cambios USB
VOLUME_SAVE_DELAY = 0.6       # Reducir escrituras sobre SD
DEBUG_OSC = False             # True para diagnosticar mensajes de RNBO

# =========================================================
# ESTADO
# =========================================================
MAX_CHANNELS = 8
volumes = [0.0] * MAX_CHANNELS  # Se conservan 8 valores en JSON para futuros WAV multicanal.
wav_channels = None              # Se detecta una vez al arrancar (respaldo para /channels).
selected_channel = 0
current_screen = 0             # 0=volumen, 1=sistema, 2=reproduccion
client_osc = None
screen_dirty = True
last_screen_update = 0.0
volumes_need_save = False
last_volume_change = 0.0

# Datos entrantes de RNBO (no reemplazan los niveles del mezclador).
playback = {
    'channels': None,
    'durSeg': None,
    'seg': None,
    'loopeando': None,
}

system_info = {
    'ip': '--',
    'network': '--',
    'temp': '--',
    'ram': '--',
    'disk': '--',
    'audio': 'Buscando...',
    'audio_source': '',
    'audio_outputs': None,  # Puertos fisicos de reproduccion JACK; None = desconocido
}

ENC_STATES = [
    0, 1, -1, 0,
    -1, 0, 0, 1,
    1, 0, 0, -1,
    0, -1, 1, 0,
]

# =========================================================
# OLED
# =========================================================
device = ssd1306(i2c(port=1, address=OLED_ADDR), width=OLED_WIDTH, height=OLED_HEIGHT)
font = ImageFont.load_default()


def dirty():
    global screen_dirty
    screen_dirty = True


def text_width(draw, value):
    bbox = draw.textbbox((0, 0), str(value), font=font)
    return bbox[2] - bbox[0]


def fit_text(draw, txt, max_px):
    """Recorta en pixeles, sin suponer ancho fijo de letra."""
    txt = str(txt)
    if text_width(draw, txt) <= max_px:
        return txt
    while txt and text_width(draw, txt + '..') > max_px:
        txt = txt[:-1]
    return txt + '..'


def header(draw, title):
    draw.rectangle((0, 0, 127, 11), fill='white')
    draw.text((3, 1), title, fill='black', font=font)


def read_wav_channels(path):
    """Lee solo el encabezado del WAV, sin cargar audio ni interferir con RNBO.

    Soporta RIFF y RF64 siempre que el chunk 'fmt ' contenga los canales.
    """
    try:
        with path.open('rb') as stream:
            hdr = stream.read(12)
            if len(hdr) < 12 or hdr[:4] not in (b'RIFF', b'RF64') or hdr[8:12] != b'WAVE':
                return None
            while True:
                chunk = stream.read(8)
                if len(chunk) < 8:
                    break
                chunk_id, size = chunk[:4], struct.unpack('<I', chunk[4:])[0]
                if chunk_id == b'fmt ':
                    raw = stream.read(4)
                    if len(raw) == 4:
                        channel_count = struct.unpack('<H', raw[2:])[0]
                        return channel_count if channel_count >= 1 else None
                    break
                # Ignorar el resto del chunk sin leer el audio completo.
                stream.seek(size + (size % 2), os.SEEK_CUR)
    except (OSError, ValueError, OverflowError):
        pass
    return None


def editable_channels():
    """RNBO tiene prioridad; si no hay /channels, usa encabezado del WAV.

    El mezclador controla como maximo ocho canales; los demas no aparecen.
    Si no hay WAV ni dato OSC, conserva temporalmente los ocho controles.
    """
    channels = playback['channels'] if playback['channels'] is not None else wav_channels
    try:
        n = float(channels)
        if math.isfinite(n) and n.is_integer() and n >= 1:
            return min(MAX_CHANNELS, int(n))
    except (ValueError, TypeError, OverflowError):
        pass
    return MAX_CHANNELS


def draw_volume_screen(draw):
    """Solo dibuja los canales reportados por RNBO, centrados en la OLED."""
    count = editable_channels()
    header(draw, f'Volumen canales ({count})')
    slot_width = OLED_WIDTH / count
    bar_width = min(10, max(6, int(slot_width * .55)))
    max_bar_height = 25
    bottom_y = 48

    for i in range(count):
        vol = volumes[i]
        center_x = round((i + 0.5) * slot_width)
        bar_x = int(center_x - bar_width // 2)
        height = int(round(vol * max_bar_height))
        top_y = bottom_y - height
        val_text = str(round(vol * 100))
        value_x = max(0, min(OLED_WIDTH - text_width(draw, val_text),
                              center_x - text_width(draw, val_text) // 2))
        draw.text((value_x, 13), val_text, fill='white', font=font)
        if height > 0:
            draw.rectangle((bar_x, top_y, bar_x + bar_width - 1, bottom_y), fill='white')
        else:
            draw.line((bar_x, bottom_y, bar_x + bar_width - 1, bottom_y), fill='white')

        number = str(i + 1)
        number_x = center_x - text_width(draw, number) // 2
        if i == selected_channel:
            draw.rectangle((center_x - 7, 51, center_x + 7, 63), fill='white')
            draw.text((number_x, 52), number, fill='black', font=font)
        else:
            draw.text((number_x, 52), number, fill='white', font=font)


def scrolling_audio_label(draw, name, now, outputs):
    """Nombre de tarjeta desplazable; cantidad de salidas siempre visible a la derecha."""
    prefix = 'Audio:'
    suffix = f' O:{outputs if outputs is not None else "--"}'
    available_px = max(0, OLED_WIDTH - text_width(draw, prefix + suffix) - 2)
    name = str(name)
    if text_width(draw, name) <= available_px:
        fragment = name
    else:
        cycle = name + '   '
        offset = int(now) % len(cycle)
        repeated = cycle[offset:] + cycle[:offset] + cycle
        fragment = ''
        for char in repeated:
            if text_width(draw, fragment + char) > available_px:
                break
            fragment += char
    return prefix + fragment + suffix


def draw_system_info_screen(draw, now):
    header(draw, 'Estado del sistema')
    rows = [
        f"IP: {system_info['ip']}",
        f"Red: {system_info['network']}",
        f"Temp: {system_info['temp']} RAM: {system_info['ram']}",
        f"Disco: {system_info['disk']}",
    ]
    for idx, row in enumerate(rows):
        draw.text((0, 13 + idx * 10), fit_text(draw, row, 127), fill='white', font=font)
    audio = scrolling_audio_label(draw, system_info['audio'], now, system_info['audio_outputs'])
    draw.text((0, 53), audio, fill='white', font=font)


def format_mmss(seconds):
    """Convierte segundos a mm:ss, sin limitar el campo de minutos a 59."""
    if seconds is None:
        return '--:--'
    try:
        seconds = float(seconds)
        if not math.isfinite(seconds) or seconds < 0:
            return '--:--'
        value = int(seconds)
    except (ValueError, TypeError, OverflowError):
        return '--:--'
    minutes, secs = divmod(value, 60)
    return f'{minutes:02d}:{secs:02d}'


def draw_playback_screen(draw):
    header(draw, 'Reproduccion')
    seconds = playback['seg']
    duration = playback['durSeg']
    elapsed_text = format_mmss(seconds)
    total_text = format_mmss(duration)
    draw.text((4, 16), f'{elapsed_text} / {total_text}', fill='white', font=font)

    # La barra usa los valores reportados por RNBO, no un reloj independiente.
    try:
        duration_f = float(duration)
        elapsed_f = float(seconds)
        valid = (math.isfinite(duration_f) and math.isfinite(elapsed_f)
                 and duration_f > 0 and elapsed_f >= 0)
    except (TypeError, ValueError, OverflowError):
        valid = False

    ratio = max(0., min(1., elapsed_f / duration_f)) if valid else 0.
    draw.rectangle((4, 30, 123, 40), outline='white', fill='black')
    fill_width = int(round(116 * ratio))
    if fill_width:
        draw.rectangle((6, 32, 6 + fill_width - 1, 38), fill='white')

    progress_label = f'{round(ratio * 100):d}%' if valid else '--%'
    channels = playback['channels'] if playback['channels'] is not None else wav_channels
    ch_label = (str(int(channels)) if channels is not None and float(channels).is_integer()
                else str(channels) if channels is not None else '--')
    draw.text((4, 44), progress_label, fill='white', font=font)
    draw.text((75, 44), f'CH:{ch_label}', fill='white', font=font)

    looping = playback['loopeando']
    if looping is None:
        loop_text = '--'
    else:
        try:
            loop_text = 'SI' if float(looping) != 0 else 'NO'
        except (ValueError, TypeError):
            loop_text = str(looping)[:6]
    draw.text((4, 54), f'Loop: {loop_text}', fill='white', font=font)


def update_display():
    global screen_dirty, last_screen_update
    now = time.monotonic()
    with canvas(device) as draw:
        if current_screen == 0:
            draw_volume_screen(draw)
        elif current_screen == 1:
            draw_system_info_screen(draw, now)
        else:
            draw_playback_screen(draw)
    screen_dirty = False
    last_screen_update = now


# =========================================================
# PERSISTENCIA Y CONTROL DE VOLUMEN (rutas originales)
# =========================================================
def load_volumes():
    global volumes
    try:
        with SAVE_FILE.open('r', encoding='utf-8') as f:
            data = json.load(f)
        if isinstance(data, list) and len(data) == 8:
            vals = [float(v) for v in data]
            if all(math.isfinite(v) for v in vals):
                volumes = [max(0.0, min(1.0, v)) for v in vals]
                print(f'[PERSISTENCIA] Volumenes: {volumes}')
                return
    except (OSError, ValueError, TypeError):
        pass
    print('[PERSISTENCIA] Sin archivo valido; 8 canales en cero.')


def save_volumes():
    """Escritura atomica; se invoca una vez al terminar una serie de giros."""
    global volumes_need_save
    tmp = SAVE_FILE.with_suffix('.json.tmp')
    try:
        with tmp.open('w', encoding='utf-8') as f:
            json.dump([round(v, 3) for v in volumes], f, indent=2)
        os.replace(tmp, SAVE_FILE)
        volumes_need_save = False
    except OSError as exc:
        print(f'[PERSISTENCIA] No se pudo guardar {SAVE_FILE}: {exc}')


def schedule_save():
    global volumes_need_save, last_volume_change
    volumes_need_save = True
    last_volume_change = time.monotonic()


def sync_volumes_to_rnbo():
    if client_osc is not None:
        count = editable_channels()
        for i, v in enumerate(volumes[:count]):
            client_osc.send_message(f'/vol{i+1}', v)
        # Solo mantener la ruta agregada de ocho valores cuando hay ocho
        # controles activos; no sobrescribir los canales ocultos para WAV 6ch.
        if count == MAX_CHANNELS:
            client_osc.send_message('/volumes', volumes)
        print(f'[OSC] Volumenes iniciales sincronizados: {count} canales.')


def on_encoder_rotate(direction):
    if current_screen != 0 or selected_channel >= editable_channels():
        return
    old = volumes[selected_channel]
    new = round(max(0.0, min(1.0, old + direction * STEP_SIZE)), 3)
    if new == old:
        return
    volumes[selected_channel] = new
    dirty()
    schedule_save()
    if client_osc is not None:
        client_osc.send_message(f'/vol{selected_channel + 1}', new)


def on_button_short_press():
    global selected_channel
    if current_screen == 0:
        selected_channel = (selected_channel + 1) % editable_channels()
        print(f'[HW-040] Canal seleccionado: {selected_channel + 1}')
    elif current_screen == 1:
        print('[HW-040] Actualizando vista de sistema.')
    dirty()


def next_screen():
    global current_screen
    current_screen = (current_screen + 1) % 3
    print(f'[HW-040] Pantalla {current_screen + 1}/3')
    dirty()


async def hw040_task():
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
        new_state = (clk << 1) | dt

        if new_state != old_state:
            delta = ENC_STATES[(old_state << 2) | new_state]
            old_state = new_state
            if delta:
                accumulator += delta
                if accumulator >= DETENT_STEPS:
                    on_encoder_rotate(-1)
                    accumulator = 0
                elif accumulator <= -DETENT_STEPS:
                    on_encoder_rotate(1)
                    accumulator = 0

        now = time.monotonic()
        if GPIO.input(PIN_SW) == 0:
            if sw_pressed_time is None:
                sw_pressed_time = now
                long_press_triggered = False
            elif not long_press_triggered and now - sw_pressed_time >= LONG_PRESS_TIME:
                long_press_triggered = True
                next_screen()
        elif sw_pressed_time is not None:
            if not long_press_triggered and 0.05 < now - sw_pressed_time < LONG_PRESS_TIME:
                on_button_short_press()
            sw_pressed_time = None
            long_press_triggered = False

        # 2 ms conserva respuesta del encoder sin forzar ~1000 iteraciones/s.
        await asyncio.sleep(0.002)


# =========================================================
# OSC ENTRANTE: VOLUMENES LOCALES Y SALIDAS RNBO
# =========================================================
def volume_handler(address, *args):
    global volumes
    if not args:
        return
    changed = False
    try:
        if re.fullmatch(r'/vol[1-8]', address):
            idx = int(address[4:]) - 1
            if idx >= editable_channels():
                return  # Un canal inactivo no se modifica.
            val = max(0.0, min(1.0, float(args[0])))
            if not math.isfinite(val):
                return
            if volumes[idx] != val:
                volumes[idx] = val
                changed = True
        elif address == '/volumes' and len(args) in (editable_channels(), MAX_CHANNELS):
            vals = [max(0.0, min(1.0, float(v))) for v in args]
            if not all(math.isfinite(v) for v in vals):
                return
            count = editable_channels()
            updated = volumes[:]
            updated[:count] = vals[:count]  # No sobrescribir valores de canales ocultos.
            if volumes != updated:
                volumes = updated
                changed = True
    except (TypeError, ValueError, OverflowError):
        return

    if changed:
        if current_screen == 0:
            dirty()
        schedule_save()


def rnbo_playback_handler(address, *args):
    """Solo /channels, /durSeg, /seg y /loopeando; ignora /volumen1..8."""
    if not args:
        return
    name = address.rsplit('/', 1)[-1]
    if name not in playback:
        return
    try:
        value = float(args[0])
        if not math.isfinite(value):
            return
    except (TypeError, ValueError, OverflowError):
        return
    if playback[name] == value:
        return
    playback[name] = value
    if name == 'channels':
        # Si pasamos de 8 a 6 canales y estaba seleccionado el 7 u 8,
        # redirigir la seleccion al ultimo canal disponible.
        global selected_channel
        selected_channel = min(selected_channel, editable_channels() - 1)
        if current_screen == 0:
            dirty()
    if DEBUG_OSC:
        print(f'[RNBO] {name} = {value}')
    if current_screen == 2:
        dirty()


# =========================================================
# INFORMACION DEL SISTEMA / TARJETA DE AUDIO
# =========================================================
def get_network_info():
    ip, net_name = 'Sin IP', 'Desconectado'
    try:
        with socket.socket(socket.AF_INET, socket.SOCK_DGRAM) as s:
            s.settimeout(0.2)
            s.connect(('8.8.8.8', 80))  # UDP connect no envia paquetes
            ip = s.getsockname()[0]
        try:
            ssid = subprocess.check_output(
                ['iwgetid', '-r'], stderr=subprocess.DEVNULL, timeout=0.4,
                text=True,
            ).strip()
            net_name = ssid or 'LAN'
        except (OSError, subprocess.SubprocessError):
            net_name = 'LAN'
    except OSError:
        pass
    return ip, net_name


def system_snapshot():
    ip, network = get_network_info()
    try:
        temp = float(Path('/sys/class/thermal/thermal_zone0/temp').read_text().strip()) / 1000
        temp_str = f'{temp:.0f}C'
    except (OSError, ValueError):
        temp_str = '--'
    try:
        mem = {}
        for line in Path('/proc/meminfo').read_text().splitlines():
            key, _, value = line.partition(':')
            if key in ('MemTotal', 'MemAvailable'):
                mem[key] = int(value.strip().split()[0])
        total = mem['MemTotal']
        used = total - mem['MemAvailable']
        ram = f'{round(used / total * 100)}%' if total else '--'
    except (OSError, KeyError, ValueError, ZeroDivisionError):
        ram = '--'
    try:
        usage = shutil.disk_usage('/')
        disk = f'{round(usage.used / usage.total * 100)}% ({usage.used / 2**30:.1f}G)'
    except (OSError, ZeroDivisionError):
        disk = '--'
    return {'ip': ip, 'network': network, 'temp': temp_str, 'ram': ram, 'disk': disk}


def query_runner(path):
    """Devuelve el nodo OSCQuery (JSON) sin bibliotecas HTTP adicionales."""
    try:
        with urlopen(RUNNER_HTTP + path, timeout=0.6) as response:
            return json.load(response)
    except (OSError, ValueError):
        return None


def oscquery_value(node):
    if not isinstance(node, dict):
        return None
    val = node.get('VALUE')
    if isinstance(val, list):
        return val[0] if val else None
    return val


def audio_card_from_runner():
    """Prioriza la tarjeta SELECCIONADA por RNBO/JACK, no la primera ALSA."""
    selected = oscquery_value(query_runner('/rnbo/jack/config/card'))
    if not isinstance(selected, str) or not selected:
        return None
    cards = query_runner('/rnbo/jack/info/alsa_cards')
    if isinstance(cards, dict):
        entry = cards.get('CONTENTS', {}).get(selected)
        description = oscquery_value(entry)
        if isinstance(description, str) and description.strip():
            first_line = description.splitlines()[0].strip()
            human_name = first_line.split(' - ', 1)[-1].strip()
            return human_name or selected
    return selected  # No afirmar que su descripcion ALSA esta disponible


def audio_card_from_alsa():
    """Alternativa si RNBO no esta disponible; muestra dispositivo detectado."""
    try:
        cards = Path('/proc/asound/cards').read_text()
    except OSError:
        return 'Sin tarjeta'
    lines = re.findall(r'^\s*(\d+)\s+\[([^\]]+)\]\s*:\s*(.+)$', cards, re.M)
    if not lines:
        return 'Sin tarjeta'
    # Preferir USB, DAC, HiFiBerry o Pisound a las salidas integradas HDMI.
    scored = []
    for number, short, desc in lines:
        line = f'{short} {desc}'
        score = (3 if re.search(r'USB|HiFiBerry|Pisound|DAC|ES-8|Scarlett', line, re.I)
                 else 0)
        score -= 2 if re.search(r'HDMI|bcm2835', line, re.I) else 0
        scored.append((score, int(number), desc.split(' - ', 1)[-1].strip() or short))
    scored.sort(key=lambda e: (-e[0], e[1]))
    return scored[0][2]


def jack_playback_outputs():
    """Cuenta los puertos de salida fisicos de audio expuestos por JACK.

    El JACK backend nombra habitualmente las salidas 'system:playback_1', etc.
    Esas entradas fisicas reciben audio desde RNBO. No se cuentan puertos
    'rnbo0:out1' porque son salidas del patch, NO de la tarjeta.
    Devuelve None si no se puede comprobar; evita inventar salidas.
    """
    try:
        proc = subprocess.run(
            ['jack_lsp', '-p'], capture_output=True, text=True,
            timeout=2.0, check=False,
        )
    except (OSError, subprocess.SubprocessError):
        return None
    if proc.returncode != 0:
        return None

    ports = []
    current_name = None
    for line in proc.stdout.splitlines():
        if line and not line[0].isspace():
            current_name = line.strip()
        elif current_name and line.strip().lower().startswith('properties:'):
            flags = set(re.findall(r'[a-z]+', line.lower().split(':', 1)[1]))
            if ('input' in flags and 'physical' in flags
                    and re.search(r':playback_\d+$', current_name, re.I)):
                ports.append(current_name)
    return len(set(ports)) if ports else None


def audio_info_snapshot():
    rnbo_name = audio_card_from_runner()
    if rnbo_name:
        # JACK usa la interfaz elegida por RNBO. Se mide la cantidad de
        # puertos de playback disponibles en esa configuracion en uso.
        return rnbo_name, 'RNBO/JACK (configurada)', jack_playback_outputs()
    # No atribuir el conteo de JACK a una tarjeta ALSA no confirmada.
    return audio_card_from_alsa(), 'ALSA (detectada, no confirma uso)', None


# =========================================================
# TAREAS ASINCRONAS
# =========================================================
async def system_task():
    last_audio_check = -1e12
    while True:
        # syscalls/red/HTTP van a un worker, para no retrasar el encoder/OSC.
        snapshot = await asyncio.to_thread(system_snapshot)
        changed = any(system_info.get(k) != v for k, v in snapshot.items())
        system_info.update(snapshot)
        now = time.monotonic()
        if now - last_audio_check >= AUDIO_REFRESH_SECONDS:
            audio_name, source, outputs = await asyncio.to_thread(audio_info_snapshot)
            if system_info['audio_outputs'] != outputs:
                system_info['audio_outputs'] = outputs
                changed = True
                print(f'[AUDIO] Puertos de reproduccion JACK: {outputs if outputs is not None else "no disponibles"}')
            if system_info['audio'] != audio_name:
                system_info['audio'] = audio_name
                changed = True
            if source != system_info['audio_source']:
                system_info['audio_source'] = source
                print(f'[AUDIO] {audio_name} ({source}) | salidas JACK: {outputs if outputs is not None else "no detectadas"}')
            last_audio_check = now
        if changed and current_screen == 1:
            dirty()
        await asyncio.sleep(SYS_REFRESH_SECONDS)


async def display_task():
    last_scroll_second = None
    while True:
        now = time.monotonic()
        if current_screen == 1 and last_scroll_second != int(now):
            last_scroll_second = int(now)
            # Solo animar el texto si el nombre excede el ancho de una fila.
            if len(system_info['audio']) > 9:
                dirty()
        if screen_dirty and now - last_screen_update >= 1.0 / DISPLAY_FPS:
            update_display()
        if volumes_need_save and now - last_volume_change >= VOLUME_SAVE_DELAY:
            save_volumes()
        await asyncio.sleep(0.05)


async def init_osc():
    global client_osc
    dispatcher = Dispatcher()
    for i in range(1, 9):
        dispatcher.map(f'/vol{i}', volume_handler)
    dispatcher.map('/volumes', volume_handler)
    for name in playback:
        dispatcher.map(f'{OSC_OUT_BASE}/{name}', rnbo_playback_handler)

    loop = asyncio.get_running_loop()
    server = AsyncIOOSCUDPServer((OSC_BIND_IP, OSC_PORT), dispatcher, loop)
    transport, protocol = await server.create_serve_endpoint()

    client_osc = SimpleUDPClient(OSC_TX_IP, OSC_TX_PORT)
    client_osc.send_message('/rnbo/listeners/add', f'{OSC_LISTENER_IP}:{OSC_PORT}')
    print(f'[OSC] Local UDP {OSC_PORT}; RNBO {OSC_TX_IP}:{OSC_TX_PORT}')
    print(f'[OSC] Listener agregado: {OSC_LISTENER_IP}:{OSC_PORT}')
    print(f'[OSC] Salidas RNBO: {", ".join(playback)}')
    return transport, protocol


async def main():
    global wav_channels
    load_volumes()
    wav_channels = read_wav_channels(WAV_FILE)
    if wav_channels is not None:
        print(f'[WAV] {WAV_FILE.name}: {wav_channels} canales')
    update_display()
    transport = None
    tasks = []
    try:
        transport, _ = await init_osc()
        sync_volumes_to_rnbo()
        tasks = [
            asyncio.create_task(hw040_task(), name='encoder'),
            asyncio.create_task(system_task(), name='system'),
            asyncio.create_task(display_task(), name='display'),
        ]
        stop = asyncio.Event()
        loop = asyncio.get_running_loop()
        for sig in (signal.SIGTERM, signal.SIGINT):
            try:
                loop.add_signal_handler(sig, stop.set)
            except NotImplementedError:
                signal.signal(sig, lambda *_: stop.set())

        # Salir ante señal o fallo de tarea, sin quedar detenido indefinidamente.
        wait_stop = asyncio.create_task(stop.wait())
        done, _ = await asyncio.wait([wait_stop] + tasks, return_when=asyncio.FIRST_COMPLETED)
        if wait_stop not in done:
            for task in done:
                if task.exception():
                    raise task.exception()
        wait_stop.cancel()
    finally:
        for task in tasks:
            task.cancel()
        if tasks:
            await asyncio.gather(*tasks, return_exceptions=True)
        if volumes_need_save:
            save_volumes()
        if client_osc is not None:
            client_osc.send_message('/rnbo/listeners/del', f'{OSC_LISTENER_IP}:{OSC_PORT}')
        if transport is not None:
            transport.close()
        device.clear()
        GPIO.cleanup()
        print('[SISTEMA] Info finalizado.')


if __name__ == '__main__':
    try:
        asyncio.run(main())
    except KeyboardInterrupt:
        pass

# RNBO + Raspberry Pi + OLED SSD1306 128×64

## Archivos

- `inicio.py`: punto de entrada. Si no hay USB espera 5 segundos y abre `info.py`; si hay una USB con un único WAV, copia el archivo a `/home/pi/Documents/rnbo/datafiles/archivoAReproducir.wav`, desmonta y espera que se retire la USB antes de iniciar `info.py`. Conserva la lógica de la versión proporcionada. Se corrigió únicamente la activación temprana del `venv`.
- `info.py`: monitor OSC/OLED y control de ocho volúmenes por encoder HW-040. Conserva los GPIO BCM 17/27/22, rutas OSC de volumen `/vol1` a `/vol8` y `/volumes`, persistencia `volumes.json` y pantalla de barras.

## Navegación (HW-040)

- Pulsación larga de **2 segundos**: Volumen → Sistema → Reproducción → Volumen.
- Pulsación corta en Volumen: selecciona canal 1–8.
- Giro en Volumen: sube/baja 0.02 el canal seleccionado y transmite `/volN` a RNBO.
- Giro en Sistema/Reproducción: sin acción (evita cambios accidentales de volumen).

## Pantalla Sistema

Muestra IP, red, CPU, RAM, disco y tarjeta de audio. Consulta preferentemente **la tarjeta configurada en RNBO/JACK** desde la API local `http://127.0.0.1:5678/rnbo/jack/config/card`, y su nombre desde `.../rnbo/jack/info/alsa_cards`. Si el Runner no está disponible muestra una tarjeta detectada por ALSA, que **no confirma** cuál usa RNBO. Nombres largos se desplazan lentamente.

## Pantalla Reproducción

Recibe cuatro `outport` del Runner (instancia 0) por medio de un listener OSC agregado al puerto 8000:

- `/rnbo/inst/0/messages/out/seg`: posición reportada por RNBO en segundos.
- `/rnbo/inst/0/messages/out/durSeg`: duración reportada por RNBO en segundos.
- `/rnbo/inst/0/messages/out/channels`: canales reportados por RNBO.
- `/rnbo/inst/0/messages/out/loopeando`: indicador de loop reportado por RNBO.

La OLED muestra `mm:ss / mm:ss` y una barra de progreso basada en `seg/durSeg` (entre 0% y 100%). No extrapola tiempo local: si RNBO deja de enviar `seg`, la pantalla conserva el último valor. No se monitorean ni se muestran los outports `/volumen1` a `/volumen8`; **esto es distinto de los 8 volúmenes editables**.

## Transferir y ejecutar

Coloca ambos archivos en `/home/pi/`, junto a `/home/pi/venv/`:

```bash
# Desde la computadora origen: reemplaza usuario e IP
scp inicio.py info.py pi@192.168.1.100:/home/pi/

# En la Raspberry Pi
source /home/pi/venv/bin/activate
python /home/pi/inicio.py
```

Para probar solo la interfaz sin esperar USB:

```bash
/home/pi/venv/bin/python /home/pi/info.py
```

**Importante:** `inicio.py` monta y desmonta dispositivos USB, por lo que necesita ejecutarse con permisos adecuados. No se ha añadido todavía un servicio de arranque de `systemd`. RNBO Runner debe estar ejecutándose y tener cargado el patch con los `outport` indicados.

## Prueba simulada sin modificar RNBO

Con `info.py` activo, desde **otra terminal** ejecuta:

```bash
/home/pi/venv/bin/python - <<'PY'
from pythonosc.udp_client import SimpleUDPClient
c = SimpleUDPClient('127.0.0.1', 8000)
for name, value in [('channels', 8), ('durSeg', 180), ('seg', 42), ('loopeando', 1)]:
    c.send_message('/rnbo/inst/0/messages/out/' + name, value)
PY
```

Con pulsación larga hasta la tercera pantalla verás aproximadamente `00:42 / 03:00`, una barra al 23%, `CH:8` y `Loop: SI`.

## Configuración

En `info.py` puedes editar:

- `OSC_INSTANCE = 0`: si tu patch utiliza otra instancia RNBO.
- `OSC_PORT = 8000`: puerto local para OSC.
- `OSC_TX_PORT = 1234`: puerto del Runner.
- `OLED_ADDR = 0x3C`: dirección I²C.
- `DISPLAY_FPS = 8`: máximo de refrescos de OLED por segundo.
- `AUDIO_REFRESH_SECONDS = 20.0`: intervalo de consulta de tarjeta de audio.

No ejecutar `inicio.py` y `info.py` en paralelo: comparten una misma OLED. El primero reemplaza su propio proceso con el segundo.

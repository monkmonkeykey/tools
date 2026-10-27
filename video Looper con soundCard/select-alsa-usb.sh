#!/usr/bin/env bash
# Selector de audio para Adafruit Video Looper clasico (omxplayer).
# Prioridad: primera interfaz USB con salida PCM -> ALSA; sin USB -> HDMI.
# Ejecutar como root, antes de que Supervisor inicie Video Looper.
set -euo pipefail

VIDEO_CONFIG=/boot/video_looper.ini
ASOUND_CONF=/etc/asound.conf
ASOUND_BACKUP=/etc/asound.conf.before-video-looper-audio
MARKER='# Generado por select-alsa-usb.sh'

if [[ $(id -u) -ne 0 ]]; then
    echo 'ERROR: ejecutar con sudo o como root' >&2
    exit 1
fi

if [[ ! -f "$VIDEO_CONFIG" ]]; then
    echo "ERROR: no existe $VIDEO_CONFIG" >&2
    exit 1
fi

# Verificar sintaxis y opciones; detectar claves duplicadas antes de editar.
python3 - "$VIDEO_CONFIG" <<'PY'
import configparser
import sys

config = configparser.ConfigParser(interpolation=None, strict=True)
with open(sys.argv[1], encoding='utf-8') as f:
    config.read_file(f)
for section, option in (('alsa', 'hw_device'), ('omxplayer', 'sound')):
    if not config.has_option(section, option):
        sys.exit('ERROR: falta [{}] {}'.format(section, option))
if config.get('alsa', 'hw_device').strip():
    sys.exit('ERROR: [alsa] hw_device debe quedar vacio para usar ALSA default')
PY

USB_CARD=''
# Examinar tarjetas en orden y escoger la primera USB que tenga salida PCM.
for path in /proc/asound/card[0-9]*; do
    [[ -d "$path" && -f "$path/usbid" ]] || continue
    OUTPUT_FOUND=0
    for pcm in "$path"/pcm*p; do
        if [[ -d "$pcm" ]]; then
            OUTPUT_FOUND=1
            break
        fi
    done
    [[ $OUTPUT_FOUND -eq 1 ]] || continue
    USB_CARD="${path##*card}"
    break
done

if [[ -n "$USB_CARD" ]]; then
    SOUND=alsa
    # Conservar la configuracion ALSA previa una sola vez.
    if [[ -f "$ASOUND_CONF" ]] && ! grep -Fxq "$MARKER" "$ASOUND_CONF"; then
        if [[ ! -e "$ASOUND_BACKUP" ]]; then
            cp -a "$ASOUND_CONF" "$ASOUND_BACKUP"
            echo "Respaldo ALSA creado: $ASOUND_BACKUP"
        fi
    fi

    # Crear un archivo temporal y reemplazarlo atomicamente.
    TEMP=$(mktemp /etc/.asound.conf.XXXXXX)
    printf '%s\ndefaults.pcm.card %s\ndefaults.ctl.card %s\n' \
       "$MARKER" "$USB_CARD" "$USB_CARD" > "$TEMP"
    chmod 0644 "$TEMP"
    mv -f "$TEMP" "$ASOUND_CONF"
    echo "USB/ALSA seleccionado: tarjeta $USB_CARD"
else
    SOUND=hdmi
    # No conservar un dispositivo ALSA USB que ya no esta conectado.
    # Restaurar un archivo ALSA previo solo si es el que este script respaldo.
    if [[ -f "$ASOUND_CONF" ]] && head -n 1 "$ASOUND_CONF" | grep -Fxq "$MARKER"; then
        if [[ -f "$ASOUND_BACKUP" ]]; then
            cp -a "$ASOUND_BACKUP" "$ASOUND_CONF"
            echo "Restaurada la configuracion ALSA original"
        else
            rm -f "$ASOUND_CONF"
        fi
    fi
    echo 'Sin interfaz USB de audio. Salida HDMI seleccionada.'
fi

# Editar la opcion sound SOLO en la seccion [omxplayer].
# Las opciones existentes y comentarios no se duplican ni se reescriben.
if ! grep -Eq "^[[:space:]]*sound[[:space:]]*=[[:space:]]*$SOUND([[:space:]]*([#;].*)?)?$" "$VIDEO_CONFIG"; then
    sed -i -E "/^[[:space:]]*\[omxplayer\][[:space:]]*$/,/^[[:space:]]*\[/{s/^[[:space:]]*sound[[:space:]]*=.*/sound = ${SOUND}/;}" "$VIDEO_CONFIG"
fi

# Validar nuevamente el archivo editado.
python3 - "$VIDEO_CONFIG" "$SOUND" <<'PY'
import configparser
import sys
p = configparser.ConfigParser(interpolation=None, strict=True)
with open(sys.argv[1], encoding='utf-8') as f:
    p.read_file(f)
actual = p.get('omxplayer', 'sound')
if actual != sys.argv[2]:
    sys.exit('ERROR: salida configurada {}, se esperaba {}'.format(actual, sys.argv[2]))
print('Video Looper: sound = {}'.format(actual))
PY

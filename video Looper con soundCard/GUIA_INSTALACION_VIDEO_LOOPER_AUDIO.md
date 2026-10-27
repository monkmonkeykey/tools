# Manual técnico: Video Looper con audio USB/ALSA prioritario y HDMI de respaldo

**Versión del manual:** 1.0  
**Fecha:** 26 de octubre de 2026  
**Escenario validado por el usuario:** Raspberry Pi con Adafruit Video Looper 1.0.14, Python 3.7, `omxplayer` y Supervisor.  
**Objetivo:** al arrancar, usar cualquier interfaz USB de audio que exponga una salida PCM ALSA; si no se detecta, configurar salida HDMI nativa de `omxplayer`.

> Alcance: esta guía implementa la selección de audio en un Raspberry Pi OS Legacy que ya tiene Video Looper clásico funcionando. No instala Video Looper desde cero. No es una guía universal para todas las versiones de Raspberry Pi OS o para Video Looper 2/VLC.


## 0. credenciales públicas video looper
user: pi 
pass: video


## 1. Requisitos y diagnóstico inicial

En la Raspberry Pi por SSH:

```bash
cat /etc/os-release
command -v omxplayer
command -v aplay
sudo supervisorctl status
aplay -l
ls -l /boot/video_looper.ini
systemctl list-unit-files | grep -E '^supervisor(d)?\.service'
```

Se espera encontrar `video_looper` gestionado por Supervisor, `omxplayer` instalado y `/boot/video_looper.ini` existente. Si falta `aplay` (pero el sistema es compatible), instalar `alsa-utils` con `sudo apt-get update && sudo apt-get install -y alsa-utils`. Si usa VLC o `video_looper.service`, esta implementación necesita adaptarse.

## 2. Crear respaldos

```bash
sudo cp -a /boot/video_looper.ini /boot/video_looper.ini.bak
[ ! -f /etc/asound.conf ] || sudo cp -a /etc/asound.conf /etc/asound.conf.bak
```

Si ya hay otra aplicación configurando `/etc/asound.conf`, revisa primero su contenido. El script de esta guía toma posesión de ese archivo mientras hay una interfaz USB detectada, guarda una copia inicial y la recupera cuando vuelve a HDMI.

## 3. Preparar Video Looper

Abrir:

```bash
sudo nano /boot/video_looper.ini
```

Verificar que estas opciones **existan una sola vez** en sus secciones correspondientes:

```ini
[video_looper]
video_player = omxplayer

[alsa]
hw_device =
hw_vol_file =
hw_vol_control = PCM

[omxplayer]
sound = alsa
sound_vol_file =
```

**No reemplaces el archivo entero por este fragmento:** el resto de las opciones (playlist, localización de videos, etc.) debe conservarse. `sound_vol_file =` vacío es opcional; impide que Video Looper cargue un archivo de volumen para `omxplayer`. `hw_vol_file =` vacío hace que Video Looper no fuerce el control de volumen hardware. Ninguna de estas opciones garantiza por sí sola que el mezclador de todas las interfaces esté a 0 dB.

Comprobar que el archivo no tiene opciones duplicadas:

```bash
python3 -c "import configparser; c=configparser.ConfigParser(); c.read('/boot/video_looper.ini'); print('INI válido')"
```

## 4. Instalar el selector de audio

Crear este archivo:

```bash
sudo nano /usr/local/sbin/select-alsa-usb.sh
```

Contenido completo:

```bash
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
```

Dar permisos y revisar sintaxis:

```bash
sudo chmod 755 /usr/local/sbin/select-alsa-usb.sh
sudo bash -n /usr/local/sbin/select-alsa-usb.sh
```

El selector identifica las interfaces USB por `/proc/asound/cardN/usbid` y comprueba que exista al menos un dispositivo PCM de reproducción. Elige la primera tarjeta válida. No identifica marcas: puede funcionar con M-Track Plus u otras interfaces USB compatibles con ALSA.

Con USB, actualiza `/etc/asound.conf` para que `default` apunte a la tarjeta seleccionada y ajusta `sound = alsa`. Sin USB, configura `sound = hdmi` y restaura/elimina la configuración de ALSA que haya creado este script. Para evitar opciones duplicadas, el script solo edita el valor de `sound` existente dentro de `[omxplayer]`.

## 5. Instalar el servicio systemd

Si una instalación previa lo dejó enmascarado, ejecutar primero:

```bash
sudo systemctl unmask select-alsa-usb.service
```

Crear:

```bash
sudo nano /etc/systemd/system/select-alsa-usb.service
```

Contenido completo:

```ini
[Unit]
Description=Seleccionar USB ALSA o HDMI antes de Video Looper
Wants=systemd-udev-settle.service
After=systemd-udev-settle.service
Before=supervisor.service

[Service]
Type=oneshot
ExecStart=/usr/local/sbin/select-alsa-usb.sh

[Install]
WantedBy=multi-user.target
```

`Before=supervisor.service` garantiza la precedencia **si el servicio que gestiona Supervisor se llama exactamente `supervisor.service`** y ambos trabajos se incluyen en el arranque. Si la distribución usa otro nombre (`supervisord.service`), hay que sustituir esa línea. `systemd-udev-settle.service` espera a que se procesen los eventos udev iniciales; no garantiza que dispositivos conectados tardíamente estén disponibles.

Recargar y habilitar:

```bash
sudo systemctl daemon-reload
sudo systemctl enable select-alsa-usb.service
sudo systemctl start select-alsa-usb.service
```

Revisar:

```bash
sudo systemctl status select-alsa-usb.service
sudo journalctl -u select-alsa-usb.service -n 30 --no-pager
```

Un servicio `Type=oneshot` puede quedar en `inactive (dead)` después de ejecutarse satisfactoriamente; revisar `code=exited, status=0/SUCCESS`. La habilitación se comprueba con `systemctl is-enabled select-alsa-usb.service`, que debe devolver `enabled`.

## 6. Aplicar configuración y comprobar reproducción

Con USB conectado:

```bash
sudo /usr/local/sbin/select-alsa-usb.sh
grep -n -E '^[[:space:]]*(sound|hw_device|hw_vol_file)[[:space:]]*=' /boot/video_looper.ini
cat /etc/asound.conf
sudo supervisorctl restart video_looper
sudo supervisorctl status
```

La selección esperada es `sound = alsa` y `defaults.pcm.card N` en `/etc/asound.conf` (N es el número de tarjeta USB detectada). Si Supervisor muestra `FATAL`, después de resolver el error usa `sudo supervisorctl start video_looper` en lugar de `restart`.

Opcional: detener Video Looper antes de probar los canales para evitar que ocupe la interfaz:

```bash
sudo supervisorctl stop video_looper
speaker-test -D default -c 2 -t wav -l 1
sudo supervisorctl start video_looper
```

Sin USB, repetir selección y reiniciar reproductor:

```bash
sudo systemctl restart select-alsa-usb.service
grep -n -E '^[[:space:]]*sound[[:space:]]*=' /boot/video_looper.ini
sudo supervisorctl restart video_looper
```

Debe aparecer `sound = hdmi`. Por último, ensayar las dos condiciones con reinicios reales (`sudo reboot`): (a) USB conectado y (b) sin USB.

## 7. Pruebas de aceptación

| Caso | Audio esperado | Configuración esperada |
|---|---|---|
| Interfaz USB conectada antes del arranque | Interfaz USB | `sound = alsa` |
| No hay interfaz USB al arrancar | HDMI | `sound = hdmi` |
| Cambiar a otro modelo de interfaz USB, luego arrancar | Nueva interfaz USB | `sound = alsa`, nuevo número de tarjeta |
| Conectar/desconectar USB durante la reproducción | **No soportado automáticamente** | Ejecutar manualmente el servicio y reiniciar Video Looper, o agregar udev |

El HDMI de respaldo necesita un monitor/receptor conectado y una configuración de video compatible. La selección del audio USB **no garantiza reproducción multicanal**: la compatibilidad depende de OMXPlayer, del archivo multimedia y de la interfaz.

## 8. Solución de problemas

**Video Looper no inicia — `DuplicateOptionError`:**

```bash
sudo grep -nE '^\[|^[[:space:]]*(hw_vol_file|hw_device|sound)[[:space:]]*=' /boot/video_looper.ini
python3 -c "import configparser; c=configparser.ConfigParser(); c.read('/boot/video_looper.ini'); print('INI válido')"
sudo tail -n 50 /var/log/supervisor/video_looper-stderr*
```

Quitar opciones duplicadas de la misma sección, sin eliminar los demás ajustes.

**`Unit select-alsa-usb.service is masked`:**

```bash
sudo systemctl unmask select-alsa-usb.service
sudo systemctl daemon-reload
sudo systemctl enable select-alsa-usb.service
sudo systemctl start select-alsa-usb.service
```

Si `systemctl cat select-alsa-usb.service` no muestra el archivo tras `unmask`, volver a crearlo en `/etc/systemd/system/`.

**No se detecta interfaz USB:**

```bash
cat /proc/asound/cards
aplay -l
ls -l /proc/asound/card*/usbid 2>/dev/null
```

**El servicio falla:**

```bash
sudo systemctl status select-alsa-usb.service
sudo journalctl -u select-alsa-usb.service -n 100 --no-pager
```

**El video no arranca:**

```bash
sudo supervisorctl status
sudo tail -n 80 /var/log/supervisor/video_looper-stderr*
```

## 9. Volver al estado anterior

Desactivar selección automática:

```bash
sudo systemctl disable --now select-alsa-usb.service
```

Restaurar el INI original (si el respaldo existe):

```bash
sudo cp -a /boot/video_looper.ini.bak /boot/video_looper.ini
```

Restaurar la configuración ALSA previa **si hay respaldo y deseas hacerlo**:

```bash
sudo cp -a /etc/asound.conf.bak /etc/asound.conf
```

Si `/etc/asound.conf` no existía antes y fue creado por el selector, puedes retirarlo tras comprobar que contiene la línea `# Generado por select-alsa-usb.sh`. Evita borrar una configuración ALSA ajena.

Reiniciar reproducción:

```bash
sudo supervisorctl restart video_looper
```

## 10. Alcance y fuentes

* Procedimiento basado en la instalación operativa del usuario: Video Looper 1.0.14, OMXPlayer y Supervisor. Los archivos de automatización son una solución personalizada, no una función oficial de Adafruit.
* Compatible conceptualmente con otras instalaciones del Video Looper clásico en Raspberry Pi OS Legacy; es necesario confirmar rutas, servicio Supervisor, utilidades ALSA y compatibilidad de OMXPlayer en cada imagen.
* Video Looper 2 con VLC y otros sistemas modernos requieren otro selector de audio y configuración del reproductor.
* Documentación oficial: https://github.com/adafruit/pi_video_looper
* Configuración oficial: https://github.com/adafruit/pi_video_looper/blob/master/assets/video_looper.ini
* Video Looper 2: https://github.com/adafruit/pi_video_looper2

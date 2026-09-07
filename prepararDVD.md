# DVD-Video 5.1 con autoplay y loop — macOS

Guía rápida para preparar un DVD-Video con audio 5.1, reproducción automática y loop continuo usando `ffmpeg`, `mplex` y `dvdauthor`.

## Archivos de partida

```text
audio.wav      # WAV multicanal 5.1, 48 kHz
video.m2v      # MPEG-2 DVD, 720×480 NTSC
```

Orden de canales usado:

```text
1 = FL
2 = FR
3 = C
4 = LFE
5 = SL
6 = SR
```

## 1. Instalar herramientas

Con Homebrew:

```bash
brew install ffmpeg mjpegtools dvdauthor
```

Herramientas utilizadas:

```text
ffmpeg / ffprobe → audio y comprobaciones
mplex            → multiplexado MPEG-2 + AC-3
dvdauthor        → estructura DVD-Video
```

## 2. Comprobar el WAV 5.1

```bash
ffprobe -v error \
-select_streams a:0 \
-show_entries stream=sample_rate,channels,channel_layout \
-of default=noprint_wrappers=1 \
"audio.wav"
```

Debe mostrar:

```text
sample_rate=48000
channels=6
```

Es posible que REAPER genere:

```text
channel_layout=unknown
```

Esto no es un problema si conocemos el orden de los seis canales.

## 3. Convertir WAV 5.1 a AC-3 5.1

```bash
ffmpeg \
-channel_layout "5.1(side)" \
-i "audio.wav" \
-c:a ac3 \
-b:a 448k \
-ar 48000 \
"audio_5.1.ac3"
```

Comprobar:

```bash
ffprobe -v error \
-select_streams a:0 \
-show_entries stream=codec_name,sample_rate,channels,channel_layout,bit_rate \
-of default=noprint_wrappers=1 \
"audio_5.1.ac3"
```

Resultado esperado:

```text
codec_name=ac3
sample_rate=48000
channels=6
channel_layout=5.1(side)
bit_rate=448000
```

## 4. Comprobar el video `.m2v`

```bash
ffprobe -v error \
-select_streams v:0 \
-show_entries stream=codec_name,width,height,r_frame_rate,avg_frame_rate,display_aspect_ratio,pix_fmt \
-of default=noprint_wrappers=1 \
"video.m2v"
```

Para un DVD NTSC 4:3:

```text
codec_name=mpeg2video
width=720
height=480
display_aspect_ratio=4:3
pix_fmt=yuv420p
r_frame_rate=30000/1001
```

Si el proyecto es widescreen, usar `16:9` en lugar de `4:3`.

## 5. Multiplexar video + AC-3

```bash
mplex -f 8 \
-o "programa_dvd.mpg" \
"video.m2v" \
"audio_5.1.ac3"
```

Esto no vuelve a codificar el video ni el audio. Crea un MPEG Program Stream adecuado para la autoría del DVD.

## 6. Comprobar el multiplexado

```bash
ffprobe -v error \
-show_entries stream=index,codec_type,codec_name,sample_rate,channels,channel_layout,width,height,r_frame_rate \
-of default=noprint_wrappers=1 \
"programa_dvd.mpg"
```

Debe contener aproximadamente:

```text
dvd_nav_packet

mpeg2video
720x480
30000/1001

ac3
48000 Hz
6 channels
5.1(side)
```

Que aparezca:

```text
codec_name=dvd_nav_packet
```

es normal.

## 7. Crear `dvd.xml`

```bash
cat > dvd.xml <<'EOF'
<dvdauthor dest="DVD_LOOP" format="ntsc">
  <vmgm />
  <titleset>
    <titles>
      <video format="ntsc" aspect="4:3" resolution="720x480" />
      <audio format="ac3" channels="6" samplerate="48khz" />
      <pgc>
        <vob file="programa_dvd.mpg" />
        <post>jump title 1;</post>
      </pgc>
    </titles>
  </titleset>
</dvdauthor>
EOF
```

La línea:

```xml
<post>jump title 1;</post>
```

hace que el título vuelva al principio cuando termina.

Importante: mantener:

```xml
<dvdauthor dest="DVD_LOOP" format="ntsc">
```

El `format="ntsc"` en el elemento raíz evita el error:

```text
ERR: no video format specified for VMGM
```

Para un DVD 16:9 cambiar:

```xml
aspect="4:3"
```

por:

```xml
aspect="16:9"
```

## 8. Crear el DVD

```bash
dvdauthor -x dvd.xml
```

Esto genera automáticamente:

```text
DVD_LOOP/
├── AUDIO_TS/
└── VIDEO_TS/
```

`AUDIO_TS` estará vacío. Esto es normal: el audio AC-3 5.1 está multiplexado dentro de los archivos `.VOB`.

## 9. Eliminar archivos `.DS_Store`

```bash
find DVD_LOOP -name ".DS_Store" -delete
```

## 10. Comprobar la estructura final

```bash
find DVD_LOOP -maxdepth 2 -type f
```

Resultado esperado:

```text
DVD_LOOP/VIDEO_TS/VIDEO_TS.BUP
DVD_LOOP/VIDEO_TS/VIDEO_TS.IFO
DVD_LOOP/VIDEO_TS/VTS_01_0.BUP
DVD_LOOP/VIDEO_TS/VTS_01_0.IFO
DVD_LOOP/VIDEO_TS/VTS_01_1.VOB
```

Dependiendo de la duración y el tamaño, pueden existir más archivos:

```text
VTS_01_2.VOB
VTS_01_3.VOB
...
```

## Flujo completo

```text
REAPER
audio.wav 5.1 / 48 kHz
        │
        ▼
      FFmpeg
        │
        ▼
audio_5.1.ac3
        │
        ├──────────────┐
        │              │
        ▼              ▼
    audio AC-3      video.m2v
        │              │
        └──────┬───────┘
               ▼
             mplex
               │
               ▼
      programa_dvd.mpg
               │
               ▼
           dvdauthor
               │
               ▼
           DVD_LOOP/
       AUDIO_TS + VIDEO_TS
               │
               ▼
              Burn
               │
               ▼
        DVD-Video 5.1
      autoplay + loop
```

## Notas

- Trabajar el audio a **48 kHz**.
- El WAV de seis canales debe respetar el orden:
  `FL, FR, C, LFE, SL, SR`.
- Para DVD NTSC se usa normalmente `720×480` a `29.97 fps`.
- `AUDIO_TS` puede estar vacío en un DVD-Video.
- Antes de quemar un DVD-R físico, conviene probar `DVD_LOOP/VIDEO_TS` en VLC u otro reproductor compatible.
- El loop del DVD puede introducir una pausa breve dependiendo del reproductor. Para instalaciones donde la continuidad sea crítica, conviene generar un programa largo con varias repeticiones internas y usar el loop del DVD como respaldo.

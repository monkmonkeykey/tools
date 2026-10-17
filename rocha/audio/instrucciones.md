# Preparación de archivo de audio

ffmpeg -i "audio.wav" \
-filter:a "pan=5.1(side)|FL=c0|FR=c1|FC=c4|LFE=c5|SL=c2|SR=c3" \
-c:a ac3 \
-b:a 448k \
-ar 48000 \
"audio_5.1.ac3"

# Preparación de archivo de video en mp4 para codificación en m2v

ffmpeg -i "video.mp4" \
-an \
-c:v mpeg2video \
-pix_fmt yuv420p \
-r 30000/1001 \
-s 720x480 \
-aspect 4:3 \
-b:v 6000k \
-maxrate 8000k \
-bufsize 1835k \
-g 18 \
"video.m2v"

## Verificación 
ffprobe -v error \
-select_streams v:0 \
-show_entries stream=codec_name,width,height,r_frame_rate,display_aspect_ratio,pix_fmt \
-of default=noprint_wrappers=1 \
"video.m2v"

# Multiplexación, creación del archivo para DVD

mplex -f 8 \
-o "programa_dvd.mpg" \
"video.m2v" \
"audio_5.1.ac3"

# Creación de archivo o instrucción para loop

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

# Creación para archivo DVD

dvdauthor -x dvd.xml

## Verificación 

find DVD_LOOP -maxdepth 2 -type f

# Creación de ISO 

hdiutil makehybrid \
-udf \
-udf-volume-name "DVD_LOOP" \
-o "DVD_LOOP.iso" \
"DVD_LOOP"
// Memoria
#include <ESP32Encoder.h>
#include <EEPROM.h>
// OLED
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
// Tsunami
#include <SparkFun_Tsunami_Qwiic.h>

// Definicón de pines para Seeed XIAO ESP32-S3
#define SDA_PIN 5         // D4 en XIAO
#define SCL_PIN 6         // D5 en XIAO
#define CLK 1             // D0 en XIAO
#define DT 2              // D1 en XIAO
#define switchChange 3    // D2 en XIAO
#define switchPantalla 4  // D3 en XIAO

#define ANCHO_PANTALLA 128
#define ALTO_PANTALLA 64

Adafruit_SSD1306 display(ANCHO_PANTALLA, ALTO_PANTALLA, &Wire, -1);
TsunamiQwiic tsunami;
ESP32Encoder encoder;

int numTracks;
int volumenCanales[8];
int canalActual = 0;
bool estado = true;

char* nombreCanales[] = {
  "CH1", "CH2", "CH3", "CH4", "CH5", "CH6", "CH7", "CH8"
};

void mostrarMensajeEnPantalla(const char* mensaje, int x, int y) {
  display.clearDisplay();
  display.setCursor(x, y);
  display.println(mensaje);
  display.display();
}

void inicializarPantalla() {
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    while (true)
      ;
  }
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.display();
}

void inicializarTsunami() {
  int intentos = 0;
  const int maxIntentos = 5;

  // Dar 1.5 segundos iniciales para que la placa Tsunami estabilice su alimentación y firmware
  mostrarMensajeEnPantalla("Iniciando Tsunami...", 0, 20);
  delay(1500);

  // Reintentar la conexión si falla
  while (tsunami.begin() == false) {
    intentos++;

    // Mostrar en pantalla el intento actual
    display.clearDisplay();
    display.setCursor(0, 10);
    display.println("Buscando Tsunami...");
    display.setCursor(0, 30);
    display.println("Intento " + String(intentos) + " de " + String(maxIntentos));
    display.display();

    if (intentos >= maxIntentos) {
      // Si falla tras todos los intentos, notificar y reiniciar el ESP32
      display.clearDisplay();
      display.setCursor(0, 20);
      display.println("Tsunami No Detectado!");
      display.setCursor(0, 40);
      display.println("Reiniciando...");
      display.display();
      delay(2000);

      ESP.restart();  // Reinicia el microcontrolador
    }

    delay(1000);  // Esperar 1 segundo antes de volver a probar
  }

  // Si logra conectarse con éxito
  mostrarMensajeEnPantalla("Tsunami Conectado!", 10, 23);
  delay(1000);
  tsunami.stopAllTracks();
}

void asignaVolumen() {
  for (int i = 0; i < numTracks; i++) {
    tsunami.masterGain(i + 1, volumenCanales[i]);
  }
}

void reproduceTsunami() {
  for (int i = 0; i < numTracks; i++) {
    tsunami.trackLoop(i + 1, true);
    tsunami.trackLoad(i + 1, i, true);
  }
  tsunami.resumeAllInSync();
}

void actualizarValorCanal() {
  int encoderDelta = encoder.getCount();
  if (encoderDelta != 0) {
    volumenCanales[canalActual] += encoderDelta;
    volumenCanales[canalActual] = constrain(volumenCanales[canalActual], -70, 4);
    encoder.setCount(0);

    // Guardar SOLO si cambió el valor
    EEPROM.writeInt(canalActual * sizeof(int), volumenCanales[canalActual]);
    EEPROM.commit();

    asignaVolumen();  // Actualiza volumen inmediatamente en la Tsunami
  }
}

void mostrarVolumenEnPantalla() {
  if (digitalRead(switchChange) == LOW) {
    canalActual = (canalActual + 1) % (numTracks > 0 ? numTracks : 1);
    Serial.print("Cambiando al canal ");
    Serial.println(canalActual);
    delay(300);  // Debounce
  }

  display.clearDisplay();
  display.setTextColor(SSD1306_BLACK, SSD1306_WHITE);
  display.setCursor(20, 1);
  display.println("Volumen canales");
  display.setTextColor(SSD1306_WHITE);

  if (numTracks <= 0) {
    display.setCursor(0, 30);
    display.println("No hay tracks que reproducir");
  } else {
    // Dibujar canales (filas superiores e inferiores)
    for (int i = 0; i < numTracks && i < 4; i++) {
      display.setCursor(i * 36, 10);
      display.println(nombreCanales[i]);
      display.setCursor(i * 36, 20);
      display.println(volumenCanales[i]);
    }
    for (int i = 4; i < numTracks && i < 8; i++) {
      display.setCursor((i - 4) * 36, 40);
      display.println(nombreCanales[i]);
      display.setCursor((i - 4) * 36, 50);
      display.println(volumenCanales[i]);
    }
  }

  display.setTextColor(SSD1306_BLACK, SSD1306_WHITE);
  display.setCursor(25, 30);
  display.println("CH actual CH " + String(canalActual + 1));
  display.setTextColor(SSD1306_WHITE);
  display.display();

  actualizarValorCanal();
}

void setup() {
  Serial.begin(115200);

  // Inicializar bus I2C con los pines explícitos del XIAO ESP32-S3
  Wire.begin(SDA_PIN, SCL_PIN);

  inicializarPantalla();
  inicializarTsunami();

  numTracks = tsunami.getNumTracks();
  for (int i = 0; i < numTracks; i++) {
    tsunami.masterGain(i + 1, -10);
  }

  pinMode(switchChange, INPUT_PULLUP);
  pinMode(switchPantalla, INPUT_PULLUP);

  // Inicialización del encoder con minúscula 'up'
  ESP32Encoder::useInternalWeakPullResistors = puType::up;
  encoder.attachHalfQuad(DT, CLK);
  encoder.setCount(0);

  EEPROM.begin(512);

  // Cargar valores guardados de la EEPROM
  for (int i = 0; i < 8; i++) {
    volumenCanales[i] = EEPROM.readInt(i * sizeof(int));
    if (volumenCanales[i] < -70 || volumenCanales[i] > 4) {
      volumenCanales[i] = -10;
    }
  }

  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);

  // Nombre (Centrado en la parte superior)
  display.setCursor(22, 2);
  display.println("Raisa Pimentel");

  // Línea divisoria decorativa
  display.drawLine(10, 14, 118, 14, SSD1306_WHITE);

  // Descripción del proyecto (Centrado en el medio)
  display.setCursor(22, 22);
  display.println("Reproductor de");
  display.setCursor(16, 34);
  display.println("audio multicanal");

  // Pie de página (Abajo del todo y centrado)
  display.setCursor(25, 54);
  display.println("monkmonkeykey");

  display.display();
  delay(3000);

  mostrarMensajeEnPantalla("Tsunami Conectado", 13, 23);
  delay(1500);

  reproduceTsunami();
}

void loop() {
  if (digitalRead(switchPantalla) == LOW) {
    estado = !estado;
    delay(200);
  }

  if (estado) {
    mostrarVolumenEnPantalla();
  } else {
    display.clearDisplay();
    display.setCursor(1, 1);
    display.println(tsunami.isTrackPlaying(1) ? "Playing" : "Stopped");
    display.display();
  }
  delay(25);
}
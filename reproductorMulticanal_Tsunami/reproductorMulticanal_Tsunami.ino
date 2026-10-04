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

// Definición de pines para Seeed Studio XIAO ESP32-S3
#define SDA_PIN 5        // D4 en XIAO
#define SCL_PIN 6        // D5 en XIAO
#define CLK 1            // D0 en XIAO
#define DT 2             // D1 en XIAO
#define switchChange 3   // D2 en XIAO
#define switchPantalla 4 // D3 en XIAO

#define ANCHO_PANTALLA 128
#define ALTO_PANTALLA 64

Adafruit_SSD1306 display(ANCHO_PANTALLA, ALTO_PANTALLA, &Wire, -1);
TsunamiQwiic tsunami;
ESP32Encoder encoder;

int numTracks = 0; // Se detecta dinámicamente
int volumenCanales[8];
int canalActual = 0; // Índice virtual (0 = CH1, 1 = CH2, etc.)
bool estado = true;

// =========================================================================
// ARRAY DE MAPEO PERSONALIZABLE: Cambia estos números a tu preferencia
// Posición:         CH1, CH2, CH3, CH4, CH5, CH6, CH7, CH8
int mapeoCanales[8] = { 8,   1,   2,   3,   4,   5,   6,   7 };
// =========================================================================

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
    while (true);
  }
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.display();
}

void inicializarTsunami() {
  int intentos = 0;
  const int maxIntentos = 5;

  mostrarMensajeEnPantalla("Iniciando Tsunami...", 0, 20);
  delay(1500);

  while (tsunami.begin() == false) {
    intentos++;
    display.clearDisplay();
    display.setCursor(0, 10);
    display.println("Buscando Tsunami...");
    display.setCursor(0, 30);
    display.println("Intento " + String(intentos) + " de " + String(maxIntentos));
    display.display();

    if (intentos >= maxIntentos) {
      display.clearDisplay();
      display.setCursor(0, 20);
      display.println("Tsunami No Detectado!");
      display.setCursor(0, 40);
      display.println("Reiniciando...");
      display.display();
      delay(2000);
      ESP.restart();
    }
    delay(1000);
  }

  mostrarMensajeEnPantalla("Tsunami Conectado!", 10, 23);
  delay(1000);
  tsunami.stopAllTracks();
}

int obtenerNumeroDeTracks() {
  int count = 0;
  for (int i = 0; i < 10; i++) {
    count = tsunami.getNumTracks();
    if (count > 0) break;
    delay(150);
  }
  return count;
}

// Asigna volúmenes recorriendo el array de mapeo personalizado
void asignaVolumen() {
  for (int i = 0; i < numTracks; i++) {
    int pistaFisica = mapeoCanales[i]; // Obtiene el número de pista física desde el array
    tsunami.trackGain(pistaFisica, volumenCanales[i]); 
  }
}

// Carga y reproduce las pistas recorriendo el array de mapeo
void reproduceTsunami() {
  if (numTracks <= 0) return;
  for (int i = 0; i < numTracks; i++) {
    int pistaFisica = mapeoCanales[i];
    tsunami.trackLoop(pistaFisica, true);
    tsunami.trackLoad(pistaFisica, pistaFisica, true); 
  }
  tsunami.resumeAllInSync();
}

void actualizarValorCanal() {
  if (numTracks <= 0) return;

  int encoderDelta = encoder.getCount();
  if (encoderDelta != 0) {
    volumenCanales[canalActual] += encoderDelta;
    volumenCanales[canalActual] = constrain(volumenCanales[canalActual], -70, 4);
    encoder.setCount(0);
    
    // Pista física correspondiente según el mapeo
    int pistaFisica = mapeoCanales[canalActual];

    Serial.print("CH");
    Serial.print(canalActual + 1);
    Serial.print(" en Pantalla -> Pista/Salida Fisica ");
    Serial.print(pistaFisica);
    Serial.print(" | Vol: ");
    Serial.print(volumenCanales[canalActual]);
    Serial.println(" dB");

    // Aplicar cambio a la Tsunami
    tsunami.trackGain(pistaFisica, volumenCanales[canalActual]);

    // Guardar en EEPROM
    EEPROM.writeInt(canalActual * sizeof(int), volumenCanales[canalActual]);
    EEPROM.commit();
  }
}

void mostrarVolumenEnPantalla() {
  if (digitalRead(switchChange) == LOW) {
    if (numTracks > 0) {
      canalActual = (canalActual + 1) % numTracks;
      Serial.print("Seleccionado CH");
      Serial.print(canalActual + 1);
      Serial.print(" (Pista Fisica: ");
      Serial.print(mapeoCanales[canalActual]);
      Serial.println(")");
    }
    delay(300); // Debounce
  }

  display.clearDisplay();
  display.setTextColor(SSD1306_BLACK, SSD1306_WHITE);
  display.setCursor(20, 1);
  display.println("Volume Channels");
  display.setTextColor(SSD1306_WHITE);

  if (numTracks <= 0) {
    display.setCursor(0, 30);
    display.println("No hay tracks que reproducir");
  } else {
    for (int i = 0; i < numTracks; i++) {
      int posX = (i % 4) * 36;
      int posY = (i < 4) ? 10 : 40;
      
      display.setCursor(posX, posY);
      display.println(nombreCanales[i]);
      display.setCursor(posX, posY + 10);
      display.println(volumenCanales[i]);
    }

    display.setTextColor(SSD1306_BLACK, SSD1306_WHITE);
    display.setCursor(30, 30);
    display.println("Current CH" + String(canalActual + 1));
    display.setTextColor(SSD1306_WHITE);
  }

  display.display();

  actualizarValorCanal();
}

void setup() {
  Serial.begin(115200);
  
  Wire.begin(SDA_PIN, SCL_PIN);

  inicializarPantalla();
  
  // Pantalla de Inicio
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(22, 2);
  display.println("Raisa Pimentel");
  display.drawLine(10, 14, 118, 14, SSD1306_WHITE);
  display.setCursor(22, 22);
  display.println("Reproductor de");
  display.setCursor(16, 34);
  display.println("audio multicanal");
  display.setCursor(25, 54);
  display.println("monkmonkeykey");
  display.display();
  delay(3000);

  inicializarTsunami();

  numTracks = obtenerNumeroDeTracks();
  Serial.print("Pistas detectadas: ");
  Serial.println(numTracks);

  display.clearDisplay();
  display.setTextSize(1);
  display.setCursor(0, 28);
  display.println("Number of tracks: " + String(numTracks));
  display.display();
  delay(2000);

  pinMode(switchChange, INPUT_PULLUP);
  pinMode(switchPantalla, INPUT_PULLUP);

  ESP32Encoder::useInternalWeakPullResistors = puType::up;
  encoder.attachHalfQuad(DT, CLK);
  encoder.setCount(0);

  EEPROM.begin(512);

  // Cargar valores guardados de EEPROM
  for (int i = 0; i < 8; i++) {
    volumenCanales[i] = EEPROM.readInt(i * sizeof(int));
    if (volumenCanales[i] < -70 || volumenCanales[i] > 4) {
      volumenCanales[i] = -10;
    }
  }

  if (numTracks > 0) {
    reproduceTsunami();
    asignaVolumen();
  }
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
    display.println((numTracks > 0 && tsunami.isTrackPlaying(1)) ? "Playing" : "Stopped / No Tracks");
    display.display();
  }
  delay(25);
}
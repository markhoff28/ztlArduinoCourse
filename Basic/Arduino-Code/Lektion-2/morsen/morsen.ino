// Pseudo Morsen
// Eingebaute LED soll 1x blinken - Pause- etc. bis 5x blinken
// dann wieder von vorne

const int LED_PIN = LED_BUILTIN;

void setup() {
  pinMode(LED_PIN, OUTPUT);
  sefineLEDOutput(LED_PIN, LOW);
}

void loop() {
  // 5 x blinken
  for (int i = 1; i <= 5; i++) {
    blinkeAnzahl(i);
    delay(500);
  }
}

void blinkeAnzahl (int count) {
  for (int i = 0; i < count; i++) {
    sefineLEDOutput(LED_PIN, HIGH);
    delay(300);
    sefineLEDOutput(LED_PIN, LOW);
    delay(300);
  }
}

void sefineLEDOutput( int pinNum, int ledState) {
  digitalWrite(pinNum, ledState);
}

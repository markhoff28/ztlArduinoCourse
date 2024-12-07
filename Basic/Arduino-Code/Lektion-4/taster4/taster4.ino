const int TASTER_PIN = 8;

int tasterStatus = HIGH; // wegen PULLUP
int zaehler = 0;

void setup() {
  Serial.begin(115200);

  pinMode( TASTER_PIN, INPUT_PULLUP );
}

void loop() {
  int tasterSignal = digitalRead( TASTER_PIN );
  if (tasterSignal != tasterStatus) {
    tasterStatus = tasterSignal; // merken
    // jetzt hat sich der Zustand geändert, also Aktion ausführen
    if (tasterStatus == LOW) {
      // Taster wurde gedrückt
      zaehler++;
      Serial.println(zaehler);
    }
    delay(100); // entprellen
  }
}
const int TASTER_PIN = 8;

int tasterStatus = HIGH; // wegen PULLUP
unsigned long entprellenEndeMillis = 0;
bool entprellenAktiv = false;
const int ENTPRELL_DAUER = 100; // Millisekunden

// nach 2 Sekunden soll die Meldung "Long Press!" ausgegeben werden
unsigned long gedruecktStartZeit = 0;
bool warteAufLongPress = true;
const int LONG_PRESS_DAUER = 2000; // Millisekunden

int zaehler = 0;

void setup() {
  Serial.begin(115200);

  pinMode( TASTER_PIN, INPUT_PULLUP );
}

void loop() {
  if (entprellenAktiv) {
    // entprellenAktiv == true: warten, Taster NICHT abfragen
    if (millis() > entprellenEndeMillis) {
      entprellenAktiv = false; // Wartezeit ist abgelaufen
    }
  } else {
    int tasterSignal = digitalRead( TASTER_PIN );
    if (tasterSignal != tasterStatus) {
      tasterStatus = tasterSignal; // merken
      // jetzt hat sich der Zustand geändert, also Aktion ausführen
      if (tasterStatus == LOW) {
        // Taster wurde gedrückt
        zaehler++;
        Serial.println(zaehler);

        // Long Press Zeitmessung vorbereiten
        warteAufLongPress = true; // es wurde noch kein LP registriert
        gedruecktStartZeit = millis();
      }
      // die Entprell-Warteperiode aktivieren, sowohl für gedrückt als auch für losgelassen
      entprellenAktiv = true;
      entprellenEndeMillis = millis() + ENTPRELL_DAUER;
    }
  }

  if (tasterStatus == LOW) {
    // Taster ist gerade gedrückt
    if (warteAufLongPress) {
      if (millis() > (gedruecktStartZeit + LONG_PRESS_DAUER)) {
        Serial.println("LONG PRESS!");
        warteAufLongPress = false; // sonst wird die Meldung dauernd ab 2 Sekunden ausgegeben
      }
    }
  }

}

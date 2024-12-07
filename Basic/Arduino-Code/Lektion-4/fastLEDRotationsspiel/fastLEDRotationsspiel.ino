// FastLED library importieren
// und LED Hardware Parameter (Anzahl, Data-PIN) festlegen

#include <FastLED.h>

#define NUM_LEDS  10  // wie const int NUM_LEDS = 10;
#define DATA_PIN  2   // wie const int DATA_PIN = 2;

CRGB led_array[ NUM_LEDS ];

// Taster-Pins für linken und rechten Taster festlegen

const int TASTER_LINKS_PIN = 8;
const int TASTER_RECHTS_PIN = 9;

// Spielablauf-Variablen

// Position der aktuell leuchtenden LED (= index im Streifen)
int ledPosition = 0; // wird im loop gesetzt, im Moment 0

// Richtung der Bewegung
const int RICHTUNG_LINKS  = -1;
const int RICHTUNG_RECHTS =  1;
int ledRichtung = RICHTUNG_LINKS; // wird bei Spielstart zufällig gesetzt nach links oder rechts

// Update-Zeit der LED-Bewegung (Pause in Millisekunden zwischen LED-Updates)
unsigned long ledUpdateZeit;
int ledDelay = 150;
// Bewegung der LED alle 150 millisekunden  -> 750 Millisekunden für 5 LEDs gesamt
// Wert wird nach jeder Spielrunde runtergezählt, damit das Spiel schneller wird

void setup() {
  FastLED.addLeds<NEOPIXEL, DATA_PIN>(led_array, NUM_LEDS);
  FastLED.setMaxPowerInVoltsAndMilliamps(5, 500);

  pinMode( TASTER_LINKS_PIN,  INPUT_PULLUP );
  pinMode( TASTER_RECHTS_PIN, INPUT_PULLUP );

  spielStart();
}

void loop() {

  // Check ob nächster Spiel Schritt ausgeführt werden soll
  if (millis() > ledUpdateZeit) {
    ledUpdateZeit = millis() + ledDelay;
    
    spielAblauf();
  }

}

void spielStart() {
  // zuerst alle LEDs aus und 2 Sekunden warten
  fill_solid( &led_array[0], NUM_LEDS, CRGB::Black );
  FastLED.show();
  delay(2000);

  // Richtung links oder rechts zufällig entscheiden
  // random(2) liefert Zufallszahlen von 0 bis 1
  if (random(2) == 0) {
    ledRichtung = RICHTUNG_LINKS;
    // bei Bewegung nach links bei der 5. LED anfangen = index 4
    // und dann zu index 0 runterzählen
    ledPosition = 4;
  } else {
    ledRichtung = RICHTUNG_RECHTS;
    // bei Bewegung nach rechts bei der 6. LED anfangen = index 5
    // und dann zu index 9 hochzählen
    ledPosition = 5;
  }
}

void spielAblauf() {
  // zuerst alle LEDs aus
  fill_solid( &led_array[0], NUM_LEDS, CRGB::Black );

  // nur die aktuelle LED an in blau
  led_array[ledPosition] = CRGB::Blue;
  FastLED.show();

  // LED weiter bewegen
  ledPosition += ledRichtung;

  // sind wir über dem Spielbereich von ledPosition = 0 bis 9?
  if (ledPosition < 0) spielEnde(); // ledPosition ist = -1
  if (ledPosition == NUM_LEDS) spielEnde(); // ledPosition ist = 10
}

void spielEnde () {

  // Prüfen, ob wir gewonnen haben, dies in einer lokalen Variable 
  // "gewonnen" merken

  bool gewonnen = false;

  if (ledPosition < 0) {
    // RICHTUNG_LINKS, check ob gewonnen/verloren
    // Taster Pin = LOW: Taster ist gedrückt!
    if ((digitalRead( TASTER_LINKS_PIN  ) == LOW) && (digitalRead( TASTER_RECHTS_PIN  ) == HIGH)) {
      gewonnen = true;
    } 
  }

  if (ledPosition == NUM_LEDS) {
    // RICHTUNG_RECHTS, check ob gewonnen/verloren
    // Taster Pin = LOW: Taster ist gedrückt!
    if ((digitalRead( TASTER_LINKS_PIN  ) == HIGH) && (digitalRead( TASTER_RECHTS_PIN  ) == LOW)) {
      gewonnen = true;
    }
  }

  // Ergebnis optisch anzeigen für 1 Sekunde
  if (gewonnen) {
    fill_solid( &led_array[0], NUM_LEDS, CRGB::Green );
  } else {
    fill_solid( &led_array[0], NUM_LEDS, CRGB::Red );
  }
  FastLED.show();
  delay(1000);

  // Geschwindigkeit für die nächste Runde erhöhen
  // (immer 10 Millisekundehn schneller) bis maximal 60 Millisekunden
  // das sind dann 300 Millisekunden gesamt, also 0.3 Sekunden...
  if (ledDelay > 60) ledDelay -= 10;

  // nächste Runde starten
  spielStart();
}


#include <FastLED.h>

#define NUM_LEDS  10
#define DATA_PIN  2

CRGB led_array[ NUM_LEDS ];

unsigned long naechsteLedUpdateZeit = 0; // in Millisekunden
const int FPS = 10; // 10 Updates (frames) pro Sekunde
const int LED_UPDATE_INTERVAL = 1000/FPS; // in Millisekunden
// LED_UPDATE_INTERVAL = 100 in diesem Fall, da
// 10 Updates pro 1000 Millisekunden = 100 ms je Animationsphase

const int LAENGE_SCHWEIF = 5; // Schweif wird 5 LEDs lang
int positionKopf = -1; // Position des Kopfes, 
// von -1 (links "vor" dem Streifen)
// bis NUM_LEDS + LAENGE_SCHWEIF (rechts "hinter" dem Streifen)

CRGB farbeKomet = CRGB::Red; // später Zufallsfarbe

// Gamma-Wertetabelle
// https://learn.adafruit.com/led-tricks-gamma-correction/the-quick-fix

const uint8_t PROGMEM gamma8[] = {
    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1,  1,  1,  1,
    1,  1,  1,  1,  1,  1,  1,  1,  1,  2,  2,  2,  2,  2,  2,  2,
    2,  3,  3,  3,  3,  3,  3,  3,  4,  4,  4,  4,  4,  5,  5,  5,
    5,  6,  6,  6,  6,  7,  7,  7,  7,  8,  8,  8,  9,  9,  9, 10,
   10, 10, 11, 11, 11, 12, 12, 13, 13, 13, 14, 14, 15, 15, 16, 16,
   17, 17, 18, 18, 19, 19, 20, 20, 21, 21, 22, 22, 23, 24, 24, 25,
   25, 26, 27, 27, 28, 29, 29, 30, 31, 32, 32, 33, 34, 35, 35, 36,
   37, 38, 39, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 50,
   51, 52, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63, 64, 66, 67, 68,
   69, 70, 72, 73, 74, 75, 77, 78, 79, 81, 82, 83, 85, 86, 87, 89,
   90, 92, 93, 95, 96, 98, 99,101,102,104,105,107,109,110,112,114,
  115,117,119,120,122,124,126,127,129,131,133,135,137,138,140,142,
  144,146,148,150,152,154,156,158,160,162,164,167,169,171,173,175,
  177,180,182,184,186,189,191,193,196,198,200,203,205,208,210,213,
  215,218,220,223,225,228,231,233,236,239,241,244,247,249,252,255 };

void setup() {
  FastLED.addLeds<NEOPIXEL, DATA_PIN>(led_array, NUM_LEDS);
  FastLED.setMaxPowerInVoltsAndMilliamps(5, 500);
  randomSeed(analogRead(A0));
}

void loop() {
  if (millis() > naechsteLedUpdateZeit) {
    // naechsteLedUpdateZeit neu setzen (+100 ms)
    naechsteLedUpdateZeit = millis() + LED_UPDATE_INTERVAL;
 
    // Streifen löschen (voriger Komet wird noch angezeigt)
    fill_solid( &led_array[0], NUM_LEDS, CRGB::Black );

    // Kopf zeichnen
    //led_array[ positionKopf ] = farbeKomet;
    setzeLedAufFarbe( positionKopf, farbeKomet);
    for ( int i=0; i<LAENGE_SCHWEIF; i++ ) {
      int blendFaktor = map( i, 0, LAENGE_SCHWEIF-1, 10, 250 );
      // map-Zielbereich 10...250: 0 wäre komplett rot,
      // 255 wäre komplett schwarz - beides wollen wir nicht im Schweif
      CRGB mischFarbe = blend( farbeKomet, CRGB::Black, blendFaktor );
      //led_array[ positionKopf - i - 1 ] = mischFarbe;
      setzeLedAufFarbe( positionKopf - i - 1, mischFarbe);
    }
    FastLED.show();

    // positionKopf bewegen
    positionKopf++;
    if (positionKopf > NUM_LEDS + LAENGE_SCHWEIF) {
      farbeKomet.r = random(256); // Zufalls-Wert von 0 bis 255
      farbeKomet.g = random(256);
      farbeKomet.b = random(256);
      positionKopf = -1;
    }
  }
}

void setzeLedAufFarbe( int ledIndex, CRGB ledFarbe ) {
  // zuerst Bereich prüfen!
  if ( ledIndex < 0 ) return; // nicht ausführen, wenn -1 und kleiner
  if ( ledIndex >= NUM_LEDS) return; // nicht ausführen, wenn 10 und größer
  // jetzt ist der ledIndex sicher im Bereich von 0 bis 9 (bei NUM_LEDS = 10)

  // Gamma-Korrektur auf die r/b/b Werte anwenden
  CRGB farbeKorrigiert;
  farbeKorrigiert.r = pgm_read_byte( &gamma8[ ledFarbe.r ] );
  farbeKorrigiert.g = pgm_read_byte( &gamma8[ ledFarbe.g ] );
  farbeKorrigiert.b = pgm_read_byte( &gamma8[ ledFarbe.b ] );
  //led_array[ ledIndex ] = ledFarbe;
  led_array[ ledIndex ] = farbeKorrigiert;
}


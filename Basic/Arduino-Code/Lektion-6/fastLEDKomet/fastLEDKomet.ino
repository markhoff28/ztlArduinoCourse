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
int positionKopf = 7; // Position des Kopfes, 
// von -1 (links "vor" dem Streifen)
// bis NUM_LEDS + LAENGE_SCHWEIF (rechts "hinter" dem Streifen)
// erstmal nur fest an Position 7, ohne Animation

CRGB farbeKomet = CRGB::Red; // später Zufallsfarbe

void setup() {
  FastLED.addLeds<NEOPIXEL, DATA_PIN>(led_array, NUM_LEDS);
  FastLED.setMaxPowerInVoltsAndMilliamps(5, 500);
}

void loop() {
  if (millis() > naechsteLedUpdateZeit) {
    // naechsteLedUpdateZeit neu setzen (+100 ms)
    naechsteLedUpdateZeit = millis() + LED_UPDATE_INTERVAL;
    
    // Kopf zeichnen
    led_array[ positionKopf ] = farbeKomet;
    for ( int i=0; i<LAENGE_SCHWEIF; i++ ) {
      int blendFaktor = map( i, 0, LAENGE_SCHWEIF-1, 10, 250 );
      // map-Zielbereich 10...250: 0 wäre komplett rot,
      // 255 wäre komplett schwarz - beides wollen wir nicht im Schweif
      CRGB mischFarbe = blend( farbeKomet, CRGB::Black, blendFaktor );
      led_array[ positionKopf - i - 1 ] = mischFarbe;
    }

    FastLED.show();
  }
}


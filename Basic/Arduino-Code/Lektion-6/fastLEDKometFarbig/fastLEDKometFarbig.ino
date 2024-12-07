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
  led_array[ ledIndex ] = ledFarbe;
}


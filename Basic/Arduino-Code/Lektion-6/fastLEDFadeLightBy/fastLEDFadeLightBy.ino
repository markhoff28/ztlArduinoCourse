#include <FastLED.h>

#define NUM_LEDS  10
#define DATA_PIN  2

CRGB led_array[ NUM_LEDS ];

void setup() {
  FastLED.addLeds<NEOPIXEL, DATA_PIN>(led_array, NUM_LEDS);
  FastLED.setMaxPowerInVoltsAndMilliamps(5, 500);
}

void loop() {
  // von BLAU (i=0) zu SCHWARZ (i=255)
  for (int i=0; i<256; i++) {
    // zuerst alle LEDs mit BLAU füllen
    fill_solid( &led_array[0], NUM_LEDS, CRGB::Blue );
    // dann alle LEDs Helligkeit reduzieren
    for (int j=0; j<NUM_LEDS; j++ ) {
      led_array[j].fadeLightBy(i);
    }
    FastLED.show();
    delay(10);
  }
  // zurück von SCHWARZ (i=0) zu BLAU (i=255)
  for (int i=0; i<256; i++) {
    // zuerst alle LEDs mit BLAU füllen
    fill_solid( &led_array[0], NUM_LEDS, CRGB::Blue );
    // dann alle LEDs Helligkeit reduzieren, aber INVERTIERT (255-i)
    for (int j=0; j<NUM_LEDS; j++ ) {
      led_array[j].fadeLightBy( 255-i );
    }
    FastLED.show();
    delay(10);
  }
}


#include <FastLED.h>

#define NUM_LEDS  10
#define DATA_PIN  2

CRGB led_array[ NUM_LEDS ];

void setup() {
  FastLED.addLeds<NEOPIXEL, DATA_PIN>(led_array, NUM_LEDS);
  FastLED.setMaxPowerInVoltsAndMilliamps(5, 500);
}

void loop() {
  // von ROT (i=0) zu BLAU (i=255)
  for (int i=0; i<256; i++) {
    CRGB mischFarbe = blend( CRGB::Red, CRGB::Blue, i );
    fill_solid( &led_array[0], NUM_LEDS, mischFarbe );
    FastLED.show();
    delay(10);
  }
  // zurück von BLAU (i=0) zu ROT (i=255)
  for (int i=0; i<256; i++) {
    CRGB mischFarbe = blend( CRGB::Blue, CRGB::Red, i );
    fill_solid( &led_array[0], NUM_LEDS, mischFarbe );
    FastLED.show();
    delay(10);
  }
}
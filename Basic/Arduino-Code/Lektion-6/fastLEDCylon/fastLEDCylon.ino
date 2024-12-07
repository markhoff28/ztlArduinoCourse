#include "FastLED.h"

#define NUM_LEDS 10
#define DATA_PIN 2
CRGB leds[NUM_LEDS];

void setup() {
  FastLED.addLeds<NEOPIXEL,DATA_PIN>(leds, NUM_LEDS);
}

void loop() {
  uint8_t i = beatsin8(20,0,NUM_LEDS-1);
  leds[i] = CRGB(255,0,0);
  FastLED.show();
  fadeToBlackBy(leds,NUM_LEDS,8);
}

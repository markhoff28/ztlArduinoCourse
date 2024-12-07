#include <FastLED.h>

#define NUM_LEDS  10
#define DATA_PIN  2

CRGB led_array[ NUM_LEDS ];

int versatz = 0;
// versatz = 0,1,2 - bei 3 wieder ursprüngliche Grafik

void setup() {
  FastLED.addLeds<NEOPIXEL, DATA_PIN>(led_array, NUM_LEDS);
  FastLED.setMaxPowerInVoltsAndMilliamps(5, 500);
}

void loop() {
  for (int i=0; i<NUM_LEDS; i++) {
    if ((i - versatz) % 3 == 0) {
      // index der LED ist OHNE REST durch 3 teilbar
      // also rot
      led_array[ i ] = CRGB::Red;
    } else {
      // es gibt einen Rest beim Teilen durch 3, der
      // Index ist also kein Vielfaches von 3 -> Blau
      led_array[ i ] = CRGB::Blue;
    }
  }
  FastLED.show();
  delay(500);

  versatz++;
  if (versatz == 3) versatz = 0;
}

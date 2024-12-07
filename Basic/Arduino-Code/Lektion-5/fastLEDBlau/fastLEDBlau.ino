#include <FastLED.h>

#define NUM_LEDS  10
#define DATA_PIN  2

CRGB led_array[ NUM_LEDS ];

void setup() {
  FastLED.addLeds<NEOPIXEL, DATA_PIN>(led_array, NUM_LEDS);
  FastLED.setMaxPowerInVoltsAndMilliamps(5, 500); 
}

void loop() {
  // alle LEDs (10 Stück ab index 0) mit blau füllen
  fill_solid( &led_array[0], NUM_LEDS, CRGB::Blue );

  // 4 LEDs ab index 2 mit rot füllen
  fill_solid( &led_array[2], 4, CRGB( 0xFF0000 ) );

  // die letzte LED (index 9) mit grün füllen
  led_array[ 9 ] = CRGB(0,255,0);

  // Blauverlauf über alle 10 LEDs
  for (int i=0; i<10; i++) {
    led_array[ i ] = CRGB( 0, 0, i*25 ); // Blau-Werte von 0 bis 250
  }

  FastLED.show();
  delay(100);
}


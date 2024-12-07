#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_ST7789.h> // Hardware-specific library for ST7789
#include <SPI.h>

#define TFT_CS        10
#define TFT_RST        9
#define TFT_DC         8

Adafruit_ST7789 tft = Adafruit_ST7789(TFT_CS, TFT_DC, TFT_RST);

void setup() {

  tft.init(240, 320); // Init ST7789 320x240

  // invert nötig für Aliexpress-TFT (kein Adafruit Produkt...)
  tft.invertDisplay(false);

  tft.fillScreen(ST77XX_BLACK);

  // Kopf = gelber Kreis
  tft.fillCircle(120, 120, 100, ST77XX_YELLOW );

  // Smile = schwarzer Kreis
  tft.drawCircle(120, 120, 60, ST77XX_BLACK );

  // Smile Abdeckung unter Augen = gelbes Rechteck über Kreis
  tft.fillRect(45, 55, 150, 100, ST77XX_YELLOW );

  // Auge links = schwarzer Kreis
  tft.fillCircle(70, 80, 10, ST77XX_BLACK );

  // Auge rechts = schwarzer Kreis
  tft.fillCircle(170, 80, 10, ST77XX_BLACK );

  // NAME
  tft.setCursor( 40, 270 );
  tft.setTextSize(4);
  tft.setTextColor( ST77XX_WHITE );
  tft.println( "Magnus" );

}

void loop() {
  // wird gar nicht benötigt...
}

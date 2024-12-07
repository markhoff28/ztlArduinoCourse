#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_ST7789.h> // Hardware-specific library for ST7789
#include <SPI.h>
#include <EEPROM.h>

#define TFT_CS        10
#define TFT_RST        9
#define TFT_DC         8

Adafruit_ST7789 tft = Adafruit_ST7789(TFT_CS, TFT_DC, TFT_RST);

String defaultName = "Magnus";
String displayName = "Magnus"; // wird aus EEPROM gelesen

int adresse = 0;
char kennung[] = "NAME";

String eingabe = "";

void setup() {
  Serial.begin(115200);

  tft.init(240, 320);           // Init ST7789 320x240

  // invert nötig für Aliexpress-TFT (kein Adafruit Produkt...)
  tft.invertDisplay(false);

  displayName = leseNameEEPROM();
  Serial.println("Name aus EEPROM: " + displayName);

  zeichneBadge();
}

void zeichneBadge() {
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
  tft.println( displayName );
}

void loop() {
  eingabe = "";
  while (Serial.available() > 0) {
    eingabe += char(Serial.read());
    delay(1);
  }
  if (eingabe != "") {
    speichereNameEEPROM(eingabe);
    // zur Kontrolle: lesen und ausgeben
    displayName = leseNameEEPROM();
    Serial.println("Name aus EEPROM: " + displayName);

    zeichneBadge(); // neu zeichnen
  }
}

void speichereNameEEPROM( String eingabe ) {
  
  int eepromIndex = adresse; // ab Speicherstelle adresse schreiben

  // zuerst die Kennung schreiben
  for (int i=0; i<4; i++) {
    EEPROM.update( eepromIndex++, (byte)kennung[i] );
  }

  // dann den Eingabe-String
  for (int i=0; i<eingabe.length(); i++) {
    EEPROM.update( eepromIndex++, eingabe.charAt(i) );
  }

  // zuletzt eine Null als Zeichen für das String-Ende
  EEPROM.update( eepromIndex++, 0 );
}

String leseNameEEPROM() {
  String gelesen = ""; 

  int eepromIndex = adresse; // ab Speicherstelle adresse lesen

  // Stimmt die Kennung (= haben wir bereits einen Namen gespeichert)?
  for (int i=0; i<4; i++) {
    if (EEPROM.read( eepromIndex++ ) != kennung[i] ) {
      return defaultName; // kennung stimmt nicht, default name zurückgeben
    }
  }

  // Kennung stimmt, dann jetzt Name lesen
  // wir wissen die Länge nicht, also lesen wir bis eine 0 auftaucht
  while( EEPROM.read( eepromIndex ) != 0 ) {
    gelesen += char(EEPROM.read( eepromIndex ));
    eepromIndex++;
  }

  return gelesen;
}

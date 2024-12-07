#include <Wire.h>

const int I2C_EMPFAENGER = 0x40; // I2C-Adresse des Empfänger-Peripherals

String eingabe = "";

void setup() {
  Serial.begin( 115200 ); // für Eingabe per serieller Konsole
  Wire.begin(); // I2C als Controller starten
}

void loop() {
  eingabe = "";
  while (Serial.available() > 0) {
    eingabe += char(Serial.read());
    delay(1);
  }
  if (eingabe != "") sendeI2C( eingabe );
}

void sendeI2C( String text ) {
  Wire.beginTransmission( I2C_EMPFAENGER );
  Wire.write(text.c_str()); // kein Arduino String Objekt!
  Wire.endTransmission();
  Serial.println("Gesendet I2C: " + text);
}

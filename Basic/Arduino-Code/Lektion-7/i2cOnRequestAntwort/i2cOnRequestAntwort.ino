#include <Wire.h>

const int I2C_ADRESSE = 0x40; // unsere I2C-Adresse als Empfänger-Peripheral

void setup() {
  Serial.begin( 115200 );
  Wire.begin( I2C_ADRESSE ); // I2C als Peripeheral starten
  //Wire.onReceive(receiveEvent); // einen "interrupt handler" einrichten
  Wire.onRequest(requestEvent);
}

void loop() {
  delay(1); // hier passiert irgendwas oder gar nichts
}

void requestEvent() {
  Wire.print("Daten"); // 5 bytes (Zeichen) senden
}

#include <Wire.h>

const int I2C_ADRESSE = 0x40; // unsere I2C-Adresse als Empfänger-Peripheral

bool I2C_empfangen = false;
String I2C_message = ""; // Text der empfangenen Nachricht

void setup() {
  Serial.begin( 115200 );
  Wire.begin( I2C_ADRESSE ); // I2C als Peripeheral starten
  Wire.onReceive(receiveEvent); // einen "interrupt handler" einrichten
}

void loop() {
  delay(1); // hier passiert irgendwas oder gar nichts
  if (I2C_empfangen) {
    Serial.println("Empfangen I2C: " + I2C_message);
    I2C_empfangen = false; // Flag wieder zurücksetzen
  }
}

void receiveEvent(int numBytes) {
  I2C_message = "";

  while (Wire.available()) {
    I2C_message += char(Wire.read());
  }

  if (I2C_message.length() > 0) I2C_empfangen = true;
}

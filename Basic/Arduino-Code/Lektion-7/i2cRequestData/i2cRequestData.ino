#include <Wire.h>

// I2C-Adresse des Empfänger-Peripherals
const int I2C_EMPFAENGER = 0x40;

String I2C_message = ""; // Text der empfangenen Nachricht

void setup() {
  Serial.begin(115200);
  Wire.begin(); // I2C als Controller starten
}

void loop() {
  I2C_message = "";

  // 5 bytes (bzw. Zeichen) vom Empfänger anfordern
  Wire.requestFrom(I2C_EMPFAENGER, 31);

  while (Wire.available()) {
    I2C_message += char(Wire.read());
  }

  if (I2C_message.length() > 0) Serial.println( I2C_message );

  delay(1000); // 1 Sekunde warten
}
#include <Wire.h>

// I2C-Adresse des Empfänger-Peripherals
const int I2C_EMPFAENGER = 0x40;

byte dataArray[3] = { 0, 0, 0 };

int zaehler = 0;

void setup() {
  Wire.begin(); // controller 
}

void loop() {
  // dataArray mit 3x zaehler befüllen
  dataArray[0] = zaehler;
  dataArray[1] = zaehler;
  dataArray[2] = zaehler;
  // per I2C an peripheral senden
  sendeI2C();

  zaehler++;
  delay(1000); // 1 Sekunde warten
}

void sendeI2C() {
  Wire.beginTransmission( I2C_EMPFAENGER );
  Wire.write( dataArray, 3 );
  Wire.endTransmission();
}

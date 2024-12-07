#include <Wire.h>

const int I2C_ADRESSE = 0x40; // unsere I2C-Adresse als Empfänger-Peripheral

bool I2C_empfangen = false;
byte dataArray[3] = { 0, 0, 0 }; // empfangene Bytes

void setup() {
  Serial.begin( 115200 );
  Wire.begin( I2C_ADRESSE ); // I2C als Peripeheral starten
  Wire.onReceive(receiveEvent); // einen "interrupt handler" einrichten
}

void loop() {
  delay(1); // hier passiert irgendwas oder gar nichts
  if (I2C_empfangen) {
    // dataArray bytes ausgeben
    Serial.print("Bytes empfangen: ");
    for (int i=0; i<3; i++) {
      Serial.print( dataArray[i], HEX );
      Serial.print(" ");
    }
    Serial.println();
    I2C_empfangen = false; // Flag wieder zurücksetzen
  }
}

void receiveEvent(int numBytes) {
  int index = 0;

  while (Wire.available()) {
    dataArray[index] = Wire.read();
    index++;
    if (index == 3) break; // while-Schleife auf jeden Fall nach 3 Bytes beenden
  }

  if (index > 0) I2C_empfangen = true;
}

#include <EEPROM.h>

String defaultName = "Magnus";
String name = ""; // wird aus EEPROM gelesen

int adresse = 0;
char kennung[] = "NAME";

String eingabe = "";

void setup() {
  Serial.begin(115200);

  name = leseNameEEPROM();
  Serial.println("Name aus EEPROM: " + name);
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
    name = leseNameEEPROM();
    Serial.println("Name aus EEPROM: " + name);
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

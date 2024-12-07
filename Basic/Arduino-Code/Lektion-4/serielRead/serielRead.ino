String eingabe = "";

void setup() {
  Serial.begin( 115200 );
}

void loop() {
  eingabe = ""; // leere Zeichenkette zu Beginn

  while (Serial.available() > 0) {
    // es sind Bytes im Empfangsspeicher vorhanden
    eingabe += char( Serial.read() );
    // Byte auslesen, in Buchstabe umwandeln und an
    // "Eingabe"-Text anhängen
    delay(1); // kurz warten, ob noch Zeichen folgen
  }

  if (eingabe != "") {
    // wir haben etwas empfangen!
    Serial.print("ECHO: ");
    Serial.print(eingabe);
    // wieder in serielle Konsole ausgeben, println nicht nötig
  }
}


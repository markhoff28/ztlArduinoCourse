// Senden von Text aus der seriellen Konsole von PC A über
// Serial1 des angeschlossenen Megas auf Serial1 des Megas
// an PC B, AUsgabe des Textes in der seriellen Konsole auf PC B

// Beide Megas verbinden:
// Mega A GND -> Mega B GND
// Mega A TX1 -> Mega B RX1
// Mega A RX1 -> Mega B TX1

String eingabe = "";
String empfangen = "";

void setup() {
  // Serial (USB) für die Ein- und Ausgabe der Texte per Serieller Konsole öffnen
  Serial.begin( 115200 );

  // Serial1 zum Senden/Empfangen der Texte zum anderen Mega öffnen
  Serial1.begin( 115200 );
}

void loop() {
  
  // 1. Empfangen von Eingaben über die serielle Konsole / USB
  eingabe = ""; // leere Zeichenkette zu Beginn des loops

  while (Serial.available() > 0) {
    // es sind Bytes im Empfangsspeicher vorhanden
    eingabe += char( Serial.read() );
    // Byte auslesen, in Buchstabe umwandeln und an
    // "eingabe"-Text anhängen
    delay(1);
  }

  if (eingabe != "") {
    // wir haben etwas empfangen, diesen Text über Serial1 an den 2. Mega senden
    // println nicht nötig, da das Zeilenende bereits in eingabe enthalten ist
    Serial1.print(eingabe);

    // und als Echo zu der seriellen Konsole zurücksenden
    Serial.print("GESENDET: ");
    Serial.print(eingabe);
  }

  // 2. Empfangen von Eingaben über Serial1 vom anderen Mega
  empfangen = ""; // leere Zeichenkette zu Beginn des loops

  while (Serial1.available() > 0) {
    // es sind Bytes im Empfangsspeicher vorhanden
    empfangen += char( Serial1.read() );
    // Byte auslesen, in Buchstabe umwandeln und an
    // "empfangen"-Text anhängen
    delay(1);
  }

  if (empfangen != "") {
    // wir haben etwas empfangen, diesen Text per Serial/USb an die Serielle Konsole weitersenden
    // println nicht nötig, da das Zeilenende bereits in eingabe enthalten ist
    Serial.print("EMPFANGEN: ");
    Serial.print(empfangen);
  }
}

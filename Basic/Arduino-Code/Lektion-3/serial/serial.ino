void setup() {
  Serial.begin( 115200 ); // seriellen USB-Port mit 115200 baud öffnen
}

void loop() {
  //Serial.println("Hallo"); // String "Hallo" per USB an PC senden

  //Werte per Serial ausgeben
  Serial.println("Wert"); // gibt den Text “Wert“ in der Konsole aus
  Serial.println(10); // gibt den Text „10“ in der Konsole aus
  int wert = 20;
  // 3 Möglichkeiten, um den String „Wert = 20“ in der Konsole auszugeben:
  Serial.println("Wert = " + String(wert)); // String-Verkettung mit „+“
  Serial.print("Wert = "); // print() fügt Zeichen zur aktuellen Zeile dazu
  Serial.println(wert); // println() schließt die Zeile ab und zeigt sie an
  Serial.print("Wert = ");
  Serial.print(wert);
  Serial.println(); // „leeres“ println() zum Abschluss und Senden der Zeile
  delay(1000);
  }

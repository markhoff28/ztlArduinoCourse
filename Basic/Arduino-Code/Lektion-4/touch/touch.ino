// Touch-Modul TTP223 auslesen
// Verbindungen:
// VCC -> Mega 5V
// I/O -> Mega Pin 8
// GND -> Mega GND

const int TOUCH_IO_PIN = 8;

void setup() {
	Serial.begin(115200);
	pinMode( TOUCH_IO_PIN, INPUT );
}

void loop() {
	int touchSignal = digitalRead( TOUCH_IO_PIN );
	Serial.println( touchSignal );
  delay(100); // Wert nur 10x pro Sekunde ausgeben...
}

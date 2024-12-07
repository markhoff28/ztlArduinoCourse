const int TASTER_PIN = 8;

void setup() {
  Serial.begin(115200);

  pinMode( TASTER_PIN, INPUT );
}

void loop() {
  int tasterSignal = digitalRead( TASTER_PIN );
  Serial.println( tasterSignal );
}

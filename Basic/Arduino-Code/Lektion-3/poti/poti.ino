const int POTI_PIN = A0;

void setup() {
  Serial.begin( 115200 );
  pinMode( POTI_PIN, INPUT );
}

void loop() {
  Serial.println( analogRead(POTI_PIN) );
  delay(200);
}
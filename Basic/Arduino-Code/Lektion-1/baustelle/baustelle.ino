void setup() {
  // put your setup code here, to run once:
  pinMode(2, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(10, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(10, HIGH);
  delay(500);
  digitalWrite(8, HIGH);
  delay(500);
  digitalWrite(5, HIGH);
  delay(500);
  digitalWrite(2, HIGH);
  delay(500);
  digitalWrite(10, LOW);
  delay(500);
  digitalWrite(8, LOW);
  delay(500);
  digitalWrite(5, LOW);
  delay(1000);
  digitalWrite(2, LOW);
  delay(500);
}

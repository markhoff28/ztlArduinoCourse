const int PIN_ROT   = 4;
const int PIN_GRUEN = 3;
const int PIN_BLAU  = 2;

void setup() {
  pinMode( PIN_ROT,   OUTPUT );
  pinMode( PIN_GRUEN, OUTPUT );
  pinMode( PIN_BLAU,  OUTPUT );
}

void loop() {
  // LED leuchtet rot
  digitalWrite( PIN_ROT,   HIGH );
  digitalWrite( PIN_GRUEN, LOW  );
  digitalWrite( PIN_BLAU,  LOW  );
  delay(1000);

  // LED leuchtet grün
  digitalWrite( PIN_ROT,   LOW );
  digitalWrite( PIN_GRUEN, HIGH  );
  digitalWrite( PIN_BLAU,  LOW  );
  delay(1000);

  // LED leuchtet blau
  digitalWrite( PIN_ROT,   LOW );
  digitalWrite( PIN_GRUEN, LOW  );
  digitalWrite( PIN_BLAU,  HIGH  );
  delay(1000);

  // LED leuchtet gelb
  digitalWrite( PIN_ROT,   HIGH );
  digitalWrite( PIN_GRUEN, HIGH );
  digitalWrite( PIN_BLAU,  LOW );
  delay(1000);

  // LED leuchtet Zyan
  digitalWrite( PIN_ROT,   LOW );
  digitalWrite( PIN_GRUEN, HIGH );
  digitalWrite( PIN_BLAU,  HIGH );
  delay(1000);

  // LED leuchtet lila
  digitalWrite( PIN_ROT,   HIGH );
  digitalWrite( PIN_GRUEN, LOW );
  digitalWrite( PIN_BLAU,  HIGH );
  delay(1000);

  // LED leuchtet weiß
  digitalWrite( PIN_ROT,   HIGH );
  digitalWrite( PIN_GRUEN, HIGH );
  digitalWrite( PIN_BLAU,  HIGH );
  delay(1000);
}



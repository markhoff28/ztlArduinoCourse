const int PIN_ROT   = 4;
const int PIN_GRUEN = 3;
const int PIN_BLAU  = 2;

// Start mit Rot 100%
int wertR = 255;
int wertG = 0;
int wertB = 0;

void setup() {
  pinMode( PIN_ROT,   OUTPUT );
  pinMode( PIN_GRUEN, OUTPUT );
  pinMode( PIN_BLAU,  OUTPUT );
}

void loop() {
  // ROT RGB ( 255, 0, 0 ) zu BLAU RGB ( 0, 0, 255 )
  for (int i=0; i<255; i++) {
    setzeLedAusgaenge();
    wertR--;
    wertB++;
  }
  // BLAU RGB ( 0, 0, 255 ) zu GRÜN RGB ( 0, 255, 0 )
  for (int i=0; i<255; i++) {
    setzeLedAusgaenge();
    wertB--;
    wertG++;
  }
  // GRÜN RGB ( 0, 255, 0 ) zu ROT RGB ( 255, 0, 0 )
  for (int i=0; i<255; i++) {
    setzeLedAusgaenge();
    wertG--;
    wertR++;
  }
}

void setzeLedAusgaenge() {
  analogWrite( PIN_ROT,   wertR );
  analogWrite( PIN_GRUEN, wertG );
  analogWrite( PIN_BLAU,  wertB );
  delay(10);
}

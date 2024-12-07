const int PIN_ROT   = 4;
const int PIN_GRUEN = 3;
const int PIN_BLAU  = 2;

int wertR = 0;
int wertG = 0;
int wertB = 0;

const int POTI_PIN = A0;

void setup() {
  pinMode( PIN_ROT,   OUTPUT );
  pinMode( PIN_GRUEN, OUTPUT );
  pinMode( PIN_BLAU,  OUTPUT );

  pinMode( POTI_PIN, INPUT );
}

void loop() {
  
  int potiWert = analogRead( POTI_PIN ); // 0...1023
  int ledStufe = potiWert / 4; // 0...255

  // ledStufe   0: Farbe = Rot  ( 255,  0,   0 )
  // ledStufe 255: Farbe = Blau (   0,  0, 255 )
  wertR = 255 - ledStufe; // Poti = 0, wertR = 255 / Poti = 1023, wertR = 0
  wertB = ledStufe;       // Poti = 0, wertB =   0 / Poti = 1023, wertB = 255

  setzeLedAusgaenge();
}

void setzeLedAusgaenge() {
  analogWrite( PIN_ROT,   wertR );
  analogWrite( PIN_GRUEN, wertG );
  analogWrite( PIN_BLAU,  wertB );
  //delay(10);
}



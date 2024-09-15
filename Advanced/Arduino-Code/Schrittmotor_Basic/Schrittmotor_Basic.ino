
// Pins verbunden mit A4988 Stepper Treiber
int STEPPER_STEP_PIN = 12;
int STEPPER_ENABLE_PIN = 10;
int STEPPER_DIR_PIN = 9;

int MICROSTEP_1_PIN = 7;
int MICROSTEP_2_PIN = 6;
int MICROSTEP_3_PIN = 5;

const int microSteps = 1; // 1/2/4/8/16/256

int Pulse_pro_Umdrehung = 200;
// Motor braucht 200 Steps für eine volle 360° Drehung

int Stepper_Hertz;
// resultierende Frequenz für die STEP-Pulse, wird nachher aus RPM-Wert berechnet

int microsDelay;
// Mikrosekunden-Abstand für das manuelle Puls-Erzeugen in loop

bool motorHalten = true;

void setup() {

  // Serielle Schnittstelle öffnen zum PC über USB
  Serial.begin( 115200 );

  // Input/Output Pins initialisieren
  pinMode( STEPPER_STEP_PIN,   OUTPUT );
  pinMode( STEPPER_ENABLE_PIN, OUTPUT );
  pinMode( STEPPER_DIR_PIN,    OUTPUT );

  pinMode( MICROSTEP_1_PIN,    OUTPUT );
  pinMode( MICROSTEP_2_PIN,    OUTPUT );
  pinMode( MICROSTEP_3_PIN,    OUTPUT );

  // Microsteps

  // 1/1 - FULL STEPS / VOLLSCHRITTE
  digitalWrite(MICROSTEP_1_PIN, LOW);
  digitalWrite(MICROSTEP_2_PIN, LOW);
  digitalWrite(MICROSTEP_3_PIN, LOW);

  // 1/2 - HALF STEPS / HALBSCHRITTE
  if (microSteps == 2) {
    digitalWrite(MICROSTEP_1_PIN, HIGH);
    digitalWrite(MICROSTEP_2_PIN, LOW);
    digitalWrite(MICROSTEP_3_PIN, LOW);
  }

  // 1/4 - QUARTER STEPS / VIERTELSCHRITTE
  if (microSteps == 4) {
    digitalWrite(MICROSTEP_1_PIN, LOW);
    digitalWrite(MICROSTEP_2_PIN, HIGH);
    digitalWrite(MICROSTEP_3_PIN, LOW);
  }

  // 1/8 - EIGTH STEPS / ACHTELSCHRITTE
  if (microSteps == 8) {
    digitalWrite(MICROSTEP_1_PIN, HIGH);
    digitalWrite(MICROSTEP_2_PIN, HIGH);
    digitalWrite(MICROSTEP_3_PIN, LOW);
  }

  // 1/16 - SIXTEENTH STEPS / SECHZEHNTELSCHRITTE
  if (microSteps == 16) {
    digitalWrite(MICROSTEP_1_PIN, HIGH);
    digitalWrite(MICROSTEP_2_PIN, HIGH);
    digitalWrite(MICROSTEP_3_PIN, HIGH);
  }

  // Drehrichtung
  // LOW: von vorne gesehen im Uhrzeigersinn
  // HIGH: von vorne gesehen gegen den Uhrzeigersinn
  digitalWrite(STEPPER_DIR_PIN, LOW);

  // 1 Hz = 1 Step pro Sekunde (1 Step pro 1000 Millisekunden)
  // 100 Hz = 100 Steps pro Sekunde (1 Step pro 10 Millisekunden)
  float RPM = 2.0; // RPM = Umdrehungen pro Sekunde
  // Pulse für 1 Umdrehung (= 200 Schritte) * RPM -> Hertz (Pulse/Sekunde)
  Stepper_Hertz = RPM * Pulse_pro_Umdrehung;
  microsDelay = int(1000000.0 / Stepper_Hertz); // Mikrosekunden = 1/1000 Millisekunden = 1/1000000 Sekunden

  Serial.println("Stepper_Hertz " + String(Stepper_Hertz));
  Serial.println("microsDelay " + String(microsDelay));
}

void loop() {

  digitalWrite( STEPPER_ENABLE_PIN, LOW ); // Motor aktivieren
  // ENABLE: LOW => Aktiv, HIGH => Aus

  // 200 Schritte ausführen (= 1x 360° Umdrehung bei Vollschritten)
  for (int i=0; i<200; i++) {
    digitalWrite(STEPPER_STEP_PIN, LOW);
    delayMicroseconds( microsDelay/2 );
    digitalWrite(STEPPER_STEP_PIN, HIGH);
    delayMicroseconds( microsDelay/2 );
  }

  // entweder den Motor halten (ENABLE = LOW lassen)
  // oder freigeben (ENABLE = HIGH -> "disable")

  if (motorHalten) {
    // ENABLE ist schon auf LOW vom Bewegen zuvor
    motorHalten = false; // für nächsten Durchgang
  } else {
    digitalWrite( STEPPER_ENABLE_PIN, HIGH ); // freigeben
    motorHalten = true; // für nächsten Durchgang
  }
  // 4 Sekunde warten
  delay(4000);
}
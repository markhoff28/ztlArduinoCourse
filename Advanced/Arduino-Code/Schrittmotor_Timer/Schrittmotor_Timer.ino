// MEGA: Timer 1 / 3 / 4 / 5 nutzbar für Stepper Puls-Generierung

// Timer0 (8bit)
// nicht verwenden, wird intern für Serial u.a. benutzt

// Timer1 (16bit) wird benutzt, um die STEP-Pulssignale zu erzeugen
// OC1A Pin 11 belegt (nicht verwendbar)
// OC1B Pin 12 Puls-Ausgabe

// Timer2 (8bit)
// nicht verwenden, wird zB für Tone-Library benutzt

// Timer3 (16bit)
// OC3A Pin 5 belegt (nicht verwendbar)
// OC3B Pin 2 Puls-Ausgabe
// OC3C Pin 3 belegt (nicht verwendbar)

// Timer4 (16bit)
// OC4A Pin 6 belegt (nicht verwendbar)
// OC4B Pin 7 Puls-Ausgabe
// OC4C Pin 8 belegt (nicht verwendbar) 

// Timer5 (16bit)
// OC5A Pin 46 belegt (nicht verwendbar)
// OC5B Pin 45 Puls-Ausgabe
// OC5C Pin 44 belegt (nicht verwendbar)

// Pins verbunden mit A4988 Stepper Treiber
int STEPPER_STEP_PIN = 12; // OC1B (Puls-Ausgabe von Timer1)
// Pin 11 nicht nutzbar!
int STEPPER_ENABLE_PIN = 10;
int STEPPER_DIR_PIN = 9;
int MICROSTEP_1_PIN = 7;
int MICROSTEP_2_PIN = 6;
int MICROSTEP_3_PIN = 5;

// Timer Parameter
int Pulse_pro_Umdrehung = 200;
// Motor braucht 200 Steps für eine volle 360° Drehung

float RPM = 2.0;
// fester Wert für die Drehzahl
// durch Testen gefundene Limits: von 0.4 bis 8.0 RPM
const int microSteps = 1; // 1/2/4/8/16/256

int Stepper_Hertz;
// resultierende Frequenz aus RPM für die STEP-Pulse, wird nachher berechnet

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

  // Drehrichtung
  // LOW: von vorne gesehen im Uhrzeigersinn
  // HIGH: von vorne gesehen gegen den Uhrzeigersinn
  digitalWrite(STEPPER_DIR_PIN, LOW);

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

  // Stepper starten
  digitalWrite( STEPPER_ENABLE_PIN, LOW ); 
  // ENABLE: LOW => Aktiv, HIGH => Aus

  InitTimer(); 
  // setzt Timer1 auf die gewünschte Frequenz und startet Puls-Ausgabe

  Serial.println("Bereit");
}

void loop() {
  // leer
}

void InitTimer() {
  // Timer-Steuerung initialisieren

  Serial.println("RPM " + String(RPM));

  Stepper_Hertz = RPM * Pulse_pro_Umdrehung;
  Serial.println("Stepper_Hertz " + String(Stepper_Hertz));
  Serial.println();

  // TCCR1A Register Timer1: COM2 und WGM setzen
  // COM: 10 = nicht invertierende PWM (OC1A/OC1B beim Erreichen des Compare Wert invertieren)
  // WGM: 11 = 10 Bit PWM Betriebsart (0...1023) -> nötig für Compare Mode mit WGM12 in TCCR1B
  TCCR1A = _BV(COM1B1) | _BV(WGM11) | _BV(WGM10);

  // Obergrenze für Zähler setzen
  // Formel für CompareValue = (system-clock-freq/prescaler) / timer-freq - 1
  // system-clock-freq = Systemtakt = 16Mhz = 16000000 Hz
  // prescaler = 256 (wird weiter unten gesetzt), reduziert input clock des timers
  // max wert: 62500 (16 bit) bei Stepper_Hertz = 1
  // min wert: 0 (16 bit) bei Stepper_Hertz = 62500
  uint16_t CompareValue = (16000000/256) / Stepper_Hertz - 1;
  OCR1A = CompareValue;     // obere Grenze
  OCR1B = CompareValue / 2; // PWM duty cycle (50% OCR1A)

  // TCCRxB Register (prescaler) setzen
  // prescaler 256: CS = 100 (CS12 = 1, CS11 = 0, CS10 = 0)
  // WGM13 + WGM12: FastPWM Mode mit OCRA als TOP (wenn WGM11 und WGM10 in TCCR1A auch gesetzt sind!)
  TCCR1B = _BV(WGM13) | _BV(WGM12) | _BV(CS12);

  // das setzen von CS != 000 startet gleichzeitig den Timer
}
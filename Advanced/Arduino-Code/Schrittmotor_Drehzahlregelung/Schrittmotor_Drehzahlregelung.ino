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

// Taster
int TASTER_PIN = 2;

// Potentiometer
int POTI_PIN = A0;

// Timer Parameter
int Pulse_pro_Umdrehung = 200;
// Motor braucht 200 Steps für eine volle 360° Drehung

float RPM = 0;
// gewünschte Umdrehungen pro Minute, wird anhand Poti-Stellung berechnet
const int microSteps = 1; // 1/2/4/8/16/256

// durch Testen gefundene Limits: von 2.0 bis 8.0 RPM
float RPM_MIN = 2.0;
float RPM_MAX = 8.0;

// Hilfsvariablen für RPM Berechnung (RPM * 1000, da map() keine floats kann)
int MIN_RPM_1000;
int MAX_RPM_1000;
int RPM_1000;
int RPM_ZIEL; // Zielwert für Anfahren

int Stepper_Hertz;
// resultierende Frequenz aus RPM für die STEP-Pulse, wird nachher berechnet

bool anfahrenAktiv = true;
// ist die Anfahre-Kurve aktiv?
// beim Anfahren wird die RPM von MIN (0.8) bis zum eingestellten RPM-Wert (Poti)
// um jeweils 0.5 RPM pro 250 millisekunden erhöht
const int ANFAHR_INTERVAL = 250;

// Taster (entprellen und Status)
int tasterStatus = HIGH; // wegen PULLUP
unsigned long entprellenEndeMillis = 0;
bool entprellenAktiv = false;
const int ENTPRELL_DAUER = 100; // Millisekunden
unsigned long nextAnfahrenTime = 0;

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

  pinMode( TASTER_PIN, INPUT_PULLUP );
  pinMode( POTI_PIN, INPUT );

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

  // Stepper zu Beginn deaktivieren
  digitalWrite( STEPPER_ENABLE_PIN, HIGH ); 
  // ENABLE: LOW => Aktiv, HIGH => Aus

  // int Hilfsvariablen aus floats berechnen
  MIN_RPM_1000 = round(RPM_MIN * 1000);
  MAX_RPM_1000 = round(RPM_MAX * 1000);
  RPM_1000 = round(RPM * 1000);

  InitTimer(); 
  // setzt Timer1 auf die gewünschte Frequenz und startet Puls-Ausgabe

  Serial.println("Bereit");
}

void loop() {

  // Poti auslesen für RPM, nur wenn nicht gerade angefahren wird
  if (!anfahrenAktiv) {
    int potiWert = analogRead( POTI_PIN );
    // potiWert/8 = 0...127, damit nicht dauernd Schwankungen auftreten
    int NEW_RPM_1000 = map( potiWert/8, 0, 127, MIN_RPM_1000, MAX_RPM_1000);
    if (NEW_RPM_1000 != RPM_1000) {
      RPM_1000 = NEW_RPM_1000;
      InitTimer();
    }
  }

  // Taster auslesen für Start/Stopp
  if (entprellenAktiv) {
    // entprellenAktiv == true: warten, Taster NICHT abfragen
    if (millis() > entprellenEndeMillis) {
      entprellenAktiv = false; // Wartezeit ist abgelaufen
    }
  } else {
    int tasterSignal = digitalRead( TASTER_PIN );
    if (tasterSignal != tasterStatus) {
      tasterStatus = tasterSignal; // merken
      // jetzt hat sich der Zustand geändert, also Aktion ausführen
      if (tasterStatus == LOW) {
        // Taster wurde gedrückt
        Serial.println("START");
        anfahrenAktiv = true;
        nextAnfahrenTime = millis() + ANFAHR_INTERVAL;
        RPM_ZIEL = RPM_1000;
        RPM_1000 = MIN_RPM_1000;
        InitTimer();
        digitalWrite( STEPPER_ENABLE_PIN, LOW ); 
        // ENABLE: LOW => Aktiv, HIGH => Aus
      } else {
        Serial.println("STOP");
        digitalWrite( STEPPER_ENABLE_PIN, HIGH ); 
        // ENABLE: LOW => Aktiv, HIGH => Aus
      }
      // die Entprell-Warteperiode aktivieren, sowohl für gedrückt als auch für losgelassen
      entprellenAktiv = true;
      entprellenEndeMillis = millis() + ENTPRELL_DAUER;
    }
  }

  if (anfahrenAktiv) {
    if (millis() > nextAnfahrenTime) {
      nextAnfahrenTime = millis() + ANFAHR_INTERVAL;
      RPM_1000 += 500; // 0.5 RPM pro Schritt = 500 
      if (RPM_1000 > RPM_ZIEL) {
        RPM_1000 = RPM_ZIEL;
        anfahrenAktiv = false;
      }
      InitTimer();
    }
  }
}

void InitTimer() {
  // Timer-Steuerung initialisieren

  RPM = (float)RPM_1000 / 1000.0;
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
// Ansteuern von 2 DC-Motoren mit einem L298N Motor Shield
// Die Drehrichtung der Motoren wird über die Beschaltung der IN1/IN2-Eingänge (Motor A)
// bzw. IN3/IN4-Eingänge bestimmt
// Die Geschwindigkeit wird als PWM Signal an den Eingängen ENA und ENB geregetl
// wird ENA und ENB mit den Jumpern auf dem Motor Shield auf +5V gelegt, laufen
// die Motoren immer mit voller Geschwindigkeit (keine Regelung, 100% PWM)

// Das Potentiometer wird an Pin A0 angeschlossen, um die Drehzahl zu regulieren
#define POTI_PIN A0

// Motor A
const int ENA = 2; // GPIO muss PWM-fähig sein
const int IN1 = 3;
const int IN2 = 4;

// Motor B
const int IN3 = 5;
const int IN4 = 6;
const int ENB = 7; // GPIO muss PWM-fähig sein

int speed;

void setup() {
  // Serielle Ausgabe der Geschwindigkeit an den PC
  Serial.begin(115200);
  
  // Potentiometer
  pinMode( POTI_PIN, INPUT );
  
  // Motor
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);  
  pinMode(ENA, OUTPUT);

  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);  
  pinMode(ENB, OUTPUT);
}

void loop() {
  int potiWert = analogRead( POTI_PIN );
  
   // analogen Poti-Wert (0...1023) in PWM-Signal (0....255) umrechnen
  speed = map(potiWert, 0, 1023, 0, 255);
  Serial.println("Speed: " + String( speed ));
  
  TurnMotorA(); 
  TurnMotorB();
}

void TurnMotorA() {
  // Drehrichtung und Geschwindigkeit für Motor A setzen
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  analogWrite(ENA, speed);
}

void TurnMotorB() {
  // Drehrichtung und Geschwindigkeit für Motor B setzen
  digitalWrite(IN3, HIGH); // Drehrichtung invers zu Motor A
  digitalWrite(IN4, LOW);
  analogWrite(ENB, 255-speed); // Geschwindigkeit invers zu Motor A
}

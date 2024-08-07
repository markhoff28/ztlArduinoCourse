#include <Servo.h>

// 3 Kabel zum Servomotor
// Farben normalerweise: 
// braun oder schwarz: GND
// rot (mittleres Kabel): +5V
// gelb: PWM-Steuerungskabel (Datenleitung)

// Pin, an den die Datenleitung zum Servo angeschlossen wird
// der Pin muss PWM-fähig sein!
#define SERVO_PIN 8

// create servo object to control a servo
// twelve servo objects can be created on most boards
Servo meinServorMotor;

// Pin, an dem der Schleiferausgang des Potentiometers
// angeschlossen ist (Ax, analoger input pin)
#define POTI_PIN A0

void setup() {
  // Servo objekt initialisieren
  meinServorMotor.attach(SERVO_PIN);

  // Potentiometer-Pin initialisieren
  pinMode( POTI_PIN, INPUT );

  Serial.begin(115200);
}

void loop() {
  // Potentiometer-Stellung auslesen (Wert 0...1023)
  int potiWert = analogRead( POTI_PIN );

  // potiWert in Gradzahl (0...180) umrechnen
  int grad = map( potiWert, 0, 1023, 0, 180 );

  Serial.println("Grad: " + String( grad ));

  // Gradzahl an Servo Motor senden
  meinServorMotor.write( grad );

  // kurz warten, um dem Servo die Zeit zu geben seine
  // Position zu erreichen
  delay(20);
}

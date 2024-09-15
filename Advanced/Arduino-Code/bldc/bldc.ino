#include <Servo.h>

Servo ESC;     // create servo object to control the ESC

// Potentiometer-Schleifer an Pin A0 angeschlossen
#define POTI_PIN  A0

// ESC-PWM Signal an Pin 12 angeschlossen
#define  PWM_PIN 12

void setup() {
  Serial.begin(115200);

  pinMode(POTI_PIN, INPUT);

  // ESC-Signal an Pin 12 ausgeben
  ESC.attach(PWM_PIN,1000,2000); // (pin, min pulse width, max pulse width in microseconds)
}

void loop() {
  int potiWert = analogRead( POTI_PIN ); // Potentiometer auslesen (Wert 0...1023)
  int escSignal = map(potiWert, 0, 1023, 0, 180); // auf Wert zwischen 0...180 herunterrechnen
  ESC.write(escSignal); // und an ESC ausgeben

  Serial.println("Signal: " + String( escSignal ));
}
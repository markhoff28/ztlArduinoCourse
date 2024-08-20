#include <Servo.h>

Servo ESC;     // create servo object to control the ESC

int potValue;  // value from the analog pin
int pwmPin = 12;

void setup() {
  // Attach the ESC on pin 12
  ESC.attach(pwmPin,1000,2000); // (pin, min pulse width, max pulse width in microseconds)
  Serial.begin(115200);
}

void loop() {
  potValue = analogRead(A0);   // reads the value of the potentiometer (value between 0 and 1023)
  potValue = map(potValue, 0, 1023, 0, 180);   // scale it to use it with the servo library (value between 0 and 180)
  ESC.write(potValue);    // Send the signal to the ESC
  Serial.println("Speet: " + String( potValue ));
}
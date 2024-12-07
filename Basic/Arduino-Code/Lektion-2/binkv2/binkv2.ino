//
// 
const int LED_PIN = LED_BUILTIN;

// led state
int ledSpannung = LOW;

// Zeit in ms zu der der naechste blik
unsigned long  naechsterLEDWechsel = 0;

// 
const int blinkDauer = 1000;

// the setup function runs once when you press reset or power the board
void setup() {
  pinMode(LED_PIN, OUTPUT);
  sefineLEDOutput(LED_PIN, ledSpannung);
}

// the loop function runs over and over again forever
void loop() {


  if (millis() > naechsterLEDWechsel) {
    naechsterLEDWechsel = millis() + blinkDauer;

    if (ledSpannung == LOW) {
      ledSpannung = HIGH;
    } else {
      ledSpannung = LOW;
    }
  }
  sefineLEDOutput(LED_PIN, ledSpannung);  // turn the LED on (HIGH is the voltage level)                  // wait for a second
}

void sefineLEDOutput( int pinNum, int ledState) {
  digitalWrite(pinNum, ledState);
}
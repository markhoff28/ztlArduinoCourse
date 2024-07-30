//This code is to control the speed of a DC motor by a potentiometer using l298n driver
//We read the value from the analog input, calibrate it then inject to the module
//Refer to Surtrtech youtube channel for more information
// Source: instructables.com/Control-DC-Motor-Speed-Using-Potentiometer-L298n-A/
#define POTI_PIN A0

int in1 = 3; //Declaring where our module is wired
int in2 = 4;
int ConA = 2;// Don't forget this is a PWM DI/DO

int in3 = 5; //Declaring where our module is wired
int in4 = 6;
int ConB = 12;// Don't forget this is a PWM DI/DO
int speed;

#define POTI_PIN A0

void setup() {
  // poti
  pinMode( POTI_PIN, INPUT );
  Serial.begin(115200);
  // Motor
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);  
  pinMode(ConA, OUTPUT);
}

void TurnMotorA(int speed){ //We create a function which control the direction and speed
  digitalWrite(in1, LOW); //Switch between this HIGH and LOW to change direction
  digitalWrite(in2, HIGH);
  analogWrite(ConA,speed);// Then inject it to our motor
}

void TurnMotorB(int speed){ //We create a function which control the direction and speed
  digitalWrite(in3, LOW); //Switch between this HIGH and LOW to change direction
  digitalWrite(in4, HIGH);
  analogWrite(ConB,255-speed);// Then inject it to our motor
}

void loop() {
  int potiWert = analogRead( POTI_PIN );
  speed = potiWert*0.2492668622; //We read thea analog value from the potentiometer calibrate it
  TurnMotorA(speed); //one function that keeps looping you can add another one with different direction or stop
  TurnMotorB(speed); //one function that keeps looping you can add another one with different direction or stop
  Serial.println("Speed: " + String( speed ));
}
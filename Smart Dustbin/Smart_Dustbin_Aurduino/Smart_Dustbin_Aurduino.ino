#include <Servo.h>

#define IRSensorPin 5 // IR sensor output connected to Aries GPIO-4
#define ServoPinR 0 // Servo signal pin connected to PWM-0 of Aries Board
#define ServoPinO 2 // Servo signal pin connected to PWM-2 of Aries Board
#define LEDPin1 13 // Green LED internally connected to GPIO-13
#define LEDPin2 14 // Green LED internally connected to GPIO-14
#define MoistureSensorPin A0 // Rain sensor pin connected to A0

Servo servo1; // create servo object to control a servo1(for rotation)
Servo servo2; // create servo object to control a servo2(for opening)

void setup() {
  pinMode(IRSensorPin, INPUT); // set IR sensor pin as input
  pinMode(LEDPin1, OUTPUT); // set LED pin as output
  pinMode(LEDPin2, OUTPUT); // set LED pin as output
  servo1.attach(ServoPinR); // attach servo to PWM pin
  servo2.attach(ServoPinO); // attach servo to PWM pin
  // initialize serial communication
  Serial.begin(115200);
}

void loop() {
  int statusIRSensor = digitalRead(IRSensorPin);
  int sensorValue = analogRead(MoistureSensorPin);
  
  // IR Sensor detects object
  if (statusIRSensor ==LOW) {
    // If it's raining
    digitalWrite(LEDPin1, HIGH);
    if (sensorValue < 1750) {
      digitalWrite(LEDPin2, HIGH); // Turn On
      servo1.write(90); // Rotate servo to left (90 degrees)
      Serial.println("Object detected and wet object detected.");
      delay(4000);
    } 
    // If it's not raining
    else {
      digitalWrite(LEDPin2, LOW); // Turn off LED
      servo1.write(0); // Rotate servo to initial position
      Serial.println("Object detected and dry object detected");
    }
    servo2.write(90);
    delay(2000);
    servo2.write(0);
    delay(2000);
    servo1.write(0);
    delay(500);
  } 
  
  // IR Sensor does not detect object
  else {
    digitalWrite(LEDPin1, LOW); // Turn off LED1
    digitalWrite(LEDPin2, LOW); // Turn off LED2
    servo1.write(0); // Rotate servo to initial position
    Serial.println("No object detected.");
  }
  delay(2000);
}

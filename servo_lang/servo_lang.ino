#include <Servo.h>  // add servo library
 
Servo myservo;  // create servo object to control a servo

void setup() {
  myservo.attach(9);  // attaches the servo on pin 9 to the servo object
  Serial.begin(9600);
}
 
void loop() {
  myservo.write(90);
}
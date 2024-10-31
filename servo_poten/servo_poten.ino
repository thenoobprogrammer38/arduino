#include <Servo.h>

Servo myservo;
int potpin = 0;
int val;

const int trigPin = 9;
const int echoPin = 10;
long duration;
float distance;

void setup() {
  myservo.attach(3);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  Serial.begin(9600);
  pinMode(4, OUTPUT);
}

void loop() {
  digitalWrite(4, HIGH);
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.034 / 2;

  float height = distance  * (tan(val*(PI/180)));
  
  val = analogRead(potpin);
  val = map(val, 0, 1023, 0, 180);
  myservo.write(val);
  Serial.print("Servo Position: ");
  Serial.println(val);
  Serial.println("==================");

  if (val >= 90){
    Serial.print("Angle of Elevation: ");
    Serial.println(val-90); 
  } else {
    Serial.print("Angle of Depression: ");
    Serial.println(-1 * (90 - val));
  }


  delay(15);
  
/*
  Serial.print(" - Distance: ");
  Serial.println(distance, 2);

  
  Serial.print(" - Height: ");
  Serial.println(height, 2);
*/

}
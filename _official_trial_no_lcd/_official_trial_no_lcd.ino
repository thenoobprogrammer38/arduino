#include <Servo.h>

int potpin = 0;
int val;
Servo myservo;

const int trigPin = 9;
const int echoPin = 10;

unsigned long previousMillis = 0;
const unsigned long interval = 1000;

void setup()
{
  Serial.begin(9600);
  myservo.attach(3);  // Attaches the servo to pin 3
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
}

void loop()
{
  unsigned long currentMillis = millis();

  // Read the potentiometer
  val = analogRead(potpin);
  val = map(val, 0, 1023, 0, 180);
  
  // Measure distance with HC-SR04
  long duration;
  float distance;
  
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.034 / 2;

  int ang = 0;
  
  if (val >= 90){
    ang = val - 90;
  } 
  else {
    ang = (-1 * (90 - val));
  }

  float height = (distance) * (tan(ang * (3.14/180)));
  float hypotenuse = sqrt(pow(distance, 2) + pow (height, 2));

  // Print values every one second
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;
    
    Serial.println("=======================");
    Serial.println("NORMAL ANGLE: " + String(val) + " degrees");
    Serial.println("ANGLE: " + String(ang) + " degrees");
    Serial.println("A: " + String(distance, 2) + " cm");
    Serial.println("B: " + String(height, 2) + " cm");
    Serial.println("C: " + String(hypotenuse, 2) + " cm");
  }

  myservo.write(val);
  delay(15);
}
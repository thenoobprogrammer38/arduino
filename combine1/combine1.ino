#include <Servo.h>
#include "Wire.h"
#include "I2Cdev.h"
#include "MPU6050.h"

Servo myservo;
int potpin = 0;
int val;

const int trigPin = 9;
const int echoPin = 10;
long duration;
float distance;

MPU6050 mpu;
int16_t ax, ay, az;
int16_t gx, gy, gz;

struct MyData {
  byte X;
  byte Y;
  byte Z;
};

MyData data;

const int buzzer = 5;  // Pin connected to the LED
const int LED_PIN = 13;  // Pin connected to the LED
const int FLAT_THRESHOLD = 5000;  // Threshold value for surface detection

void setup() {
  Serial.begin(9600);
  myservo.attach(3);
  Wire.begin();
  mpu.initialize();
  pinMode(LED_PIN, OUTPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(9, OUTPUT);
}

void loop() {
  digitalWrite(4, HIGH);
  digitalWrite(9, HIGH);

  // Ultrasonic sensor distance measurement
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.034 / 2;

  // Servo control with potentiometer
  val = analogRead(potpin);
  val = map(val, 0, 1023, 0, 180);

  // MPU6050 sensor data acquisition
  mpu.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);
  data.X = map(ax, -17000, 17000, 0, 255 ); // X axis data
  data.Y = map(ay, -17000, 17000, 0, 255);
  data.Z = map(az, -17000, 17000, 0, 255);  // Y axis data

  // Surface detection using LED
  if (data.Z >= 8 && data.Z <= 13) {
    digitalWrite(LED_PIN, HIGH);

    digitalWrite(buzzer, HIGH); 
    delay (100);
    digitalWrite(buzzer, LOW); 
    delay (100);
    digitalWrite(buzzer, HIGH); 
    delay (100);
    digitalWrite(buzzer, LOW); 
    delay (100);
    digitalWrite(buzzer, HIGH); 
    delay (50);
    digitalWrite(buzzer, LOW); 
    delay (100);
    digitalWrite(buzzer, HIGH); 
    delay (50);
    digitalWrite(buzzer, LOW); 
  } else {
    digitalWrite(LED_PIN, LOW);   // Blink the LED if the surface is uneven
    delay(100);
    digitalWrite(LED_PIN, HIGH);
    delay(100);
  }

  myservo.write(val); // Set servo position after other computations
/*
  Serial.print("Servo Position: ");
  Serial.print(val);
  Serial.print(" - Distance: ");
  Serial.println(distance, 2);
*/
  Serial.print("Axis X = ");
  Serial.print(data.X);
  Serial.print("  ");
  Serial.print("Axis Y = ");
  Serial.print(data.Y);
  Serial.print("  ");
  Serial.print("Axis Z  = ");
  Serial.println(data.Z);
  
  delay(15); // Delay for the servo movement
}

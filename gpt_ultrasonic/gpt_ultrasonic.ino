/*#include <Servo.h>

Servo myservo;
int potpin = 0;
int val;

const int trigPin = 9;
const int echoPin = 10;
long duration;
float distance;

unsigned long previousMillis = 0;    // Variable to store the previous timestamp
const unsigned long ultrasonicInterval = 1000;   // Interval of 1 second for ultrasonic sensor

void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  Serial.begin(9600);
}

void loop() {

  unsigned long currentMillis = millis();   // Get the current timestamp

  if (currentMillis - previousMillis >= ultrasonicInterval) {
    previousMillis = currentMillis;    // Update the previous timestamp
    
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);

    duration = pulseIn(echoPin, HIGH);
    distance = duration * 0.034 / 2;
    
    Serial.println ("Distance: " + String(distance));
  }

  // Rest of the code continues without delay
}*/




// Define the pins for the ultrasonic sensor
const int trigPin = 9; // Trigger pin
const int echoPin = 10; // Echo pin

// Variables to store the distance and duration
long duration;
float distance;

void setup() {
  // Initialize the serial communication
  Serial.begin(9600);

  // Define the trigger and echo pins as OUTPUT and INPUT
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
}

void loop() {
  // Generate a 10us pulse on the trigger pin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Measure the duration of the pulse on the echo pin
  duration = pulseIn(echoPin, HIGH);

  // Calculate the distance in centimeters (or inches)
  distance = duration * 0.034 / 2; // Speed of sound in air is about 343 m/s

  // Print the distance to the Serial Monitor
  Serial.print("Distance: ");
  Serial.print(distance, 2);
  Serial.println(" cm");

  // You can add additional code here to take actions based on the distance measurement
  // For example, you can trigger events or control other devices based on distance.
  
  delay(1000); // Wait for a moment before taking the next measurement
}








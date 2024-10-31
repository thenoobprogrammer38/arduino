#include <Servo.h>
#include "Wire.h"
#include "I2Cdev.h"
#include "MPU6050.h"
#include <LiquidCrystal_I2C.h>

Servo myservo;
int potpin = 0;
int val;

const int trigPin = 9;
const int echoPin = 10;
long duration;
int distance;

MPU6050 mpu;
int16_t ax, ay, az;
int16_t gx, gy, gz;

struct MyData {
byte X;
byte Y;
byte Z;
};

MyData data;

const int LED_PIN = 13; // Pin connected to the LED
const int FLAT_THRESHOLD = 5000; // Threshold value for surface detection

unsigned long previousMillisServo = 0; // Variable to store the previous timestamp for servo
const unsigned long servoInterval = 15; // Interval of 15 milliseconds for servo movement

unsigned long previousMillisUltrasonic = 0; // Variable to store the previous timestamp for ultrasonic sensor
const unsigned long ultrasonicInterval = 1000; // Interval of 1 second for ultrasonic sensor

LiquidCrystal_I2C lcd(0x27, 16, 2); // set the LCD address to 0x27 for a 16 chars and 2 line display

void setup() {
myservo.attach(3);
pinMode(trigPin, OUTPUT);
pinMode(echoPin, INPUT);
Wire.begin();
mpu.initialize();
Serial.begin(9600);
pinMode(LED_PIN, OUTPUT);
pinMode(9, OUTPUT);

lcd.init(); // initialize the lcd
lcd.backlight(); // Turn on the LCD screen backlight
}

void loop() {
unsigned long currentMillis = millis(); // Get the current timestamp

// Servo control with potentiometer
if (currentMillis - previousMillisServo >= servoInterval) {
  previousMillisServo = currentMillis; // Update the previous timestamp
  val = analogRead(potpin);
val = map(val, 0, 1023, 0, 180);
myservo.write(val);

Serial.print("Servo Position: ");
Serial.print(val);
}

// Ultrasonic sensor distance measurement
if (currentMillis - previousMillisUltrasonic >= ultrasonicInterval) {
previousMillisUltrasonic = currentMillis; // Update the previous timestamp
digitalWrite(trigPin, LOW);
delayMicroseconds(2);
digitalWrite(trigPin, HIGH);
delayMicroseconds(10);
digitalWrite(trigPin, LOW);

duration = pulseIn(echoPin, HIGH);
distance = duration * 0.034 / 2;

Serial.print(" - Distance: ");
Serial.println(distance);
}

// MPU6050 sensor data acquisition
digitalWrite(9, HIGH);
mpu.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);
data.X = map(ax, -17000, 17000, 0, 255 ); // X axis data
data.Y = map(ay, -17000, 17000, 0, 255);
data.Z = map(az, -17000, 17000, 0, 255); // Y axis data

// Surface detection using LED
if (data.Z >= 8 && data.Z <= 13) {
digitalWrite(LED_PIN, HIGH); // Turn on the LED if the surface is flat
} else {
digitalWrite(LED_PIN, LOW); // Blink the LED if the surface is uneven
delay(100);
digitalWrite(LED_PIN, HIGH);
delay(100);
}

Serial.print("Axis X = ");
Serial.print(data.X);
Serial.print(" ");
Serial.print("Axis Y = ");
Serial.print(data.Y);
Serial.print(" ");
Serial.print("Axis Z = ");
Serial.println(data.Z);

// LCD display
lcd.setCursor(0, 0);
lcd.print("sin:+-.---|");

lcd.setCursor(11, 0);
lcd.print("tan:");

lcd.setCursor(0, 1);
lcd.print("cos:+-.---|");

lcd.setCursor(11, 1);
lcd.print("+-.---");

// Rest of the code continues without delay
}


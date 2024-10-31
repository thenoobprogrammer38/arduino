#include "Wire.h"
#include "I2Cdev.h"
#include "MPU6050.h"

MPU6050 mpu;
int16_t ax, ay, az;
int16_t gx, gy, gz;

struct MyData {
  byte X;
  byte Y;
  byte Z;
};

MyData data;

const int ledPin = 8;    // Pin connected to the LED
const int buzzer = 7;
const int sideLaser = 6;

int status = 0;
unsigned long previousAccelTime = 0;
const unsigned long accelInterval = 500;   // Interval for reading accelerometer data (in milliseconds)

void setup()
{
  Serial.begin(9600);
  Wire.begin();
  mpu.initialize();

  pinMode(buzzer, OUTPUT);
  pinMode(ledPin, OUTPUT);
  pinMode(sideLaser, OUTPUT);
}

void loop()
{
  digitalWrite(sideLaser, HIGH);

  unsigned long currentMillis = millis();
  
  // Read accelerometer data at the specified interval
  if (currentMillis - previousAccelTime >= accelInterval)
  {
    previousAccelTime = currentMillis;
    
    mpu.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);
    data.X = map(ax, -17000, 17000, 0, 255); // X axis data
    data.Y = map(ay, -17000, 17000, 0, 255);
    data.Z = map(az, -17000, 17000, 0, 255);  // Y axis data
  }

  if (data.Z >= 9 && data.Z < 13)
  {
    if (status == 0) {
      digitalWrite(ledPin, HIGH);
      status = 1;
      beep();
    }
  }
  else {
    // Blinking the LED
    digitalWrite(ledPin, LOW);
    delay(75);
    digitalWrite(ledPin, HIGH);
    delay(75);

    status = 0;
  }

  Serial.print("Axis X = ");
  Serial.print(data.X);
  Serial.print("  ");
  Serial.print("Axis Y = ");
  Serial.print(data.Y);
  Serial.print("  ");
  Serial.print("Axis Z  = ");
  Serial.println(data.Z);
}

// Function that makes the melody of the buzzer
void beep() {
  digitalWrite(buzzer, HIGH);
  delay(75);
  digitalWrite(buzzer, LOW);
  delay(75);
  digitalWrite(buzzer, HIGH);
  delay(75);
  digitalWrite(buzzer, LOW);
  delay(75);
  digitalWrite(buzzer, HIGH);
  delay(75);
  digitalWrite(buzzer, LOW);
  delay(75);
}

#include <Servo.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

Servo myservo;
int potpin = 0;
int val;

const int trigPin = 9;
const int echoPin = 10;
long duration;
float distance;

void setup() {
  myservo.attach(3);
  pinMode(4, OUTPUT);

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  
  Serial.begin(9600);
  lcd.init();
  lcd.backlight();
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
  
  val = analogRead(potpin);
  val = map(val, 0, 1023, 0, 180);
  myservo.write(val);
  delay(15);

  Serial.print("Servo Position: ");
  Serial.print(val);

  Serial.print(" - Distance: ");
  Serial.println(distance, 2);

  lcd.setCursor(1, 0);
  lcd.print("Labing kanos mo");
}

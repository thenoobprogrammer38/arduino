#include <Servo.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SH1106.h>
#include <Keypad.h>
#include <EEPROM.h>

int potpin = 0;
int val;
Servo myservo;

const int trigPin = 9;
const int echoPin = 10;

//laser pins
const int servoLaser = 11;
const int constantLaser = 12;

const float rad = 0.01745329252;
unsigned long previousMillis = 0;
const unsigned long interval = 1000;

//oled displays
#define OLED_RESET -1
Adafruit_SH1106 display(OLED_RESET);

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

//keypad variables
const byte ROWS = 1;
const byte COLS = 3;

char keys[ROWS][COLS] = {
  { '1', '2', '3' }
};

byte rowPins[ROWS] = { 4 };
byte colPins[COLS] = { 5, 6, 7 };

Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

//extra variables
int button = 50;
bool paused = false;


void setup() {
  Serial.begin(9600);

  myservo.attach(3);  // servo to pin 3

  //ultrasonic sensor
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  //servo
  pinMode(servoLaser, OUTPUT);
  pinMode(constantLaser, OUTPUT);

  //oled displays
  display.begin(SH1106_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();
}



void loop() {
  unsigned long currentMillis = millis();

  //on the lasers
  digitalWrite(servoLaser, HIGH);
  digitalWrite(constantLaser, HIGH);

  // Read the potentiometer
  val = analogRead(potpin);
  val = map(val, 0, 1023, 1, 180);

  // distance variables
  long duration;
  float distance;

  //measuring distance
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = ((duration / 2) / 29.1) + 0.6;  // add 0.6 for the average deviation

  //Negating the Angle
  int ang = 0;
  if (val >= 90 && val < 180) {
    ang = val - 90;
  } else if (val >= 180) {
    ang = 89;
  } else {
    ang = -1 * (90 - val);
  }

  //Height and Hypotenuse Variables
  float height = (distance) * (tan(ang * rad));
  float hypotenuse = sqrt(pow(height, 2) + pow(distance, 2));

  //absolute value the negative height
  if (ang < 0) {
    height = -1 * height;
  }

  char key = keypad.getKey();
  int state = int(key);

  // Print values every one second
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;

    //Trigonometric Ratios Formula
    float sinx = sin(ang * rad);
    float cosx = cos(ang * rad);
    float tanx = tan(ang * rad);
    float cscx = 1 / sinx;
    float secx = 1 / cosx;
    float cotx = 1 / tanx;

    //Radians Calculation
    int degrees = abs(ang);
    float radians = degrees * 3.14159 / 180.0;

    // Calculate Fraction Form
    int numerator = round(radians * 180.0 / 3.14159);
    int denominator = 180;

    // Find the greatest common divisor
    int gcd = findGCD(numerator, denominator);

    // Simplify the fraction
    numerator /= gcd;
    denominator /= gcd;

    //area of triangle
    float area = 0.5 * (distance * height);



    //save button
    //saveMeasurements();




    //main function or measuring - button 3
    if (ang == 0) {
      zeroAngle(ang, distance, height, hypotenuse, sinx, cosx, secx, tanx);  //zero angle display
      radianAngle(ang, numerator, denominator);                              //radian conversion

      test(ang, height, distance, hypotenuse);
    }

    else {
      notZeroAngle(ang, area, height, distance, hypotenuse, sinx, cosx, tanx, cscx, secx, cotx);  //notzeroangle display
      radianAngle(ang, numerator, denominator);                                                   //radian conversion

      test(ang, height, distance, hypotenuse);
    }

    //convert function here button 2
    //convertMeasurements();




  }
  myservo.write(val);
  delay(15);  //writing the servo with little delay

  display.display();  //oled refresh
}

// Function to find the greatest common divisor (Euclidean algorithm)
int findGCD(int a, int b) {
  while (b != 0) {
    int temp = b;
    b = a % b;
    a = temp;
  }
  return a;
}
#include <Servo.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SH1106.h>

int potpin = 0;
int val;
Servo myservo;

const int trigPin = 9;
const int echoPin = 10;

//laser pins
const int servoLaser = 4;
const int constantLaser = 5;

const float rad = 0.01745329252;
unsigned long previousMillis = 0;
const unsigned long interval = 1000;

//oled displays
#define OLED_RESET -1
Adafruit_SH1106 display(OLED_RESET);

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64


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
  val = map(val, 0, 1023, 0, 184);
  

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
  distance = duration * 0.034 / 2;

  //Negating the Angle
  int ang = 0;
  if (val >= 90 && val < 180) {
    ang = val - 90;
  } else if (val >= 180) {
    ang = 90;
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

    //Configuring the 2 LCD Displays
    if (ang >= 90 || ang == -90) {

      //initialize lcd
      display.clearDisplay();
      display.setTextSize(1);
      display.setTextColor(WHITE);

      //group 1 display
      display.setCursor(0, 0);
      display.write(223);  //alpha symbol
      display.print(": " + String(ang));
      display.setCursor(0, 8);
      display.write(224);  //beta symbol
      display.print(": " + String(90));
      display.setCursor(0, 16);
      display.print("a: " + String(area, 2));

      //group 2 display
      display.setCursor(68, 0);
      display.print("A:INF");
      display.setCursor(68, 8);
      display.print("B: " + String(distance, 1));
      display.setCursor(68, 16);
      display.println("C:INF");

      display.setCursor(0, 24);
      display.print("---------------------");

      //degree display
      display.setCursor(0, 32);
      display.print("deg: " + String(ang));


      //testinggggggggggggggggggggggggggggggggggggggggggggggggg
      Serial.println("Angle: " + String(ang, 1));
      Serial.println("A:INF");
      Serial.println("B:" + String(distance, 1));
      Serial.println("C:INF");
      Serial.println("========================\n");


      if (ang < 0) {
        if (numerator == 1) {
          display.setCursor(68, 32);
          display.print("r:-");
          display.write(226);  //pi symbol
          display.print("/" + String(denominator));
        } 
        else {
          display.setCursor(68, 32);
          display.print("r:-" + String(numerator));
          display.write(226);  //pi symbol
          display.print("/" + String(denominator));
        }
      } else {
        if (numerator == 1) {
          display.setCursor(68, 32);
          display.print("r: ");
          display.write(226);  //pi symbol
          display.print("/" + String(denominator));
        } else if (numerator < 10) {
          display.setCursor(68, 32);
          display.print("r: " + String(numerator));
          display.write(226);  //pi symbol
          display.print("/" + String(denominator));
        } else if (numerator >= 10) {
          display.setCursor(68, 32);
          display.print("r: " + String(numerator));
          display.write(226);  //pi symbol
          display.print("/" + String(denominator));
        }
      }

      //ratios display
      //sines
      display.setCursor(0, 40);
      display.print("sin: " + String(sinx, 2));
      display.setCursor(68, 40);
      display.print("csc: " + String(cscx, 2));

      //cosines
      display.setCursor(0, 48);
      display.print("cos: " + String(cosx, 2));
      display.setCursor(68, 48);
      display.print("sec: INF");

      //tans
      display.setCursor(0, 56);
      display.print("tan: INF");
      display.setCursor(68, 56);
      display.print("cot: " + String(cotx, 2));
    }

    else if (ang == 0){
      display.setCursor(68, 32);
      display.print("r: " + String(numerator));
      display.write(226);  //pi symbol
      display.print("/" + String(denominator));
    }

    else if (ang >= -5 && ang <= -1) {

      //initialize lcd
      display.clearDisplay();
      display.setTextSize(1);
      display.setTextColor(WHITE);

      //group 1 display
      display.setCursor(0, 0);
      display.write(223);  //alpha symbol
      display.print(": " + String(ang));
      display.setCursor(0, 8);
      display.write(224);  //beta symbol
      display.print(": " + String(90- abs(ang)));
      display.setCursor(0, 16);
      display.print("a: " + String(area, 2));

      //group 2 display
      display.setCursor(68, 0);
      display.print("A: " + String(height, 1));
      display.setCursor(68, 8);
      display.print("B: " + String(distance, 1));
      display.setCursor(68, 16);
      display.println("C: " + String(hypotenuse, 1));

      display.setCursor(0, 24);
      display.print("---------------------");

      //degree display
      display.setCursor(0, 32);
      display.print("deg: " + String(ang));


      //Testingggggggggggggggggggggggggggggggggg
      Serial.println("Angle: " + String(ang));
      Serial.println("A:" + String(height, 1));
      Serial.println("B:" + String(distance, 1));
      Serial.println("C:" + String(hypotenuse, 1));
      Serial.println("========================\n");


      if (ang < 0) {
        if (numerator == 1) {
          display.setCursor(68, 32);
          display.print("r:-");
          display.write(226);  //pi symbol
          display.print("/" + String(denominator));
        } else {
          display.setCursor(68, 32);
          display.print("r:-" + String(numerator));
          display.write(226);  //pi symbol
          display.print("/" + String(denominator));
        }
      } else {
        if (numerator == 1) {
          display.setCursor(68, 32);
          display.print("r: ");
          display.write(226);  //pi symbol
          display.print("/" + String(denominator));
        } else {
          display.setCursor(68, 32);
          display.print("r: " + String(numerator));
          display.write(226);  //pi symbol
          display.print("/" + String(denominator));
        }
      }

      //ratios display
      //sines
      display.setCursor(0, 40);
      display.print("sin: " + String(sinx, 2));
      display.setCursor(68, 40);
      display.print("csc: " + String(cscx, 2));

      //cosines
      display.setCursor(0, 48);
      display.print("cos: " + String(cosx, 2));
      display.setCursor(68, 48);
      display.print("sec: " + String(secx, 2));

      //tans
      display.setCursor(0, 56);
      display.print("tan: " + String(cotx, 2));
      display.setCursor(68, 56);
      display.print("cot: " + String(cotx, 2));
    } else {
      //initialize lcd
      display.clearDisplay();
      display.setTextSize(1);
      display.setTextColor(WHITE);

      //group 1 display
      display.setCursor(0, 0);
      display.write(223);  //alpha symbol
      display.print(": " + String(ang));
      display.setCursor(0, 8);
      display.write(224);  //beta symbol
      display.print(": " + String(90- abs(ang)));
      display.setCursor(0, 16);
      display.print("a: " + String(area, 2));

      //group 2 display
      display.setCursor(68, 0);
      display.print("A: " + String(height, 1));
      display.setCursor(68, 8);
      display.print("B: " + String(distance, 1));
      display.setCursor(68, 16);
      display.println("C: " + String(hypotenuse, 1));

      display.setCursor(0, 24);
      display.print("---------------------");

      //degree display
      display.setCursor(0, 32);
      display.print("deg: " + String(ang));

      //testing
      Serial.println("Angle: " + String(ang));
      Serial.println("A:" + String(height, 1));
      Serial.println("B:" + String(distance, 1));
      Serial.println("C:" + String(hypotenuse, 1));
      Serial.println("========================\n");

      if (ang < 0) {
        if (numerator == 1) {
          display.setCursor(68, 32);
          display.print("r:-");
          display.write(226);  //pi symbol
          display.print("/" + String(denominator));
        } else {
          display.setCursor(68, 32);
          display.print("r:-" + String(numerator));
          display.write(226);  //pi symbol
          display.print("/" + String(denominator));
        }
      } else {
        if (numerator == 1) {
          display.setCursor(68, 32);
          display.print("r: ");
          display.write(226);  //pi symbol
          display.print("/" + String(denominator));
        } else {
          display.setCursor(68, 32);
          display.print("r: " + String(numerator));
          display.write(226);  //pi symbol
          display.print("/" + String(denominator));
        }
      }
      //ratios display
      //sines
      display.setCursor(0, 40);
      display.print("sin: " + String(sinx, 2));
      display.setCursor(68, 40);
      display.print("csc: " + String(cscx, 2));

      //cosines
      display.setCursor(0, 48);
      display.print("cos: " + String(cosx, 2));
      display.setCursor(68, 48);
      display.print("sec: " + String(secx, 2));

      //tans
      display.setCursor(0, 56);
      display.print("tan: " + String(cotx, 2));
      display.setCursor(68, 56);
      display.print("cot: " + String(cotx, 2));
    }
  }

  //writing the servo with no delay
  myservo.write(val);
  delay(15);

  //oled refresh
  display.display();

  Serial.println(val);
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
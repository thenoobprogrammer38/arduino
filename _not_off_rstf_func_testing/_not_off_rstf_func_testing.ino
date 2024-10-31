#include <Servo.h>
#include <Wire.h>
#include <Keypad.h>
#include <EEPROM.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SH1106.h>

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

    //area of triangle
    float area = 0.5 * (distance * height);
    //perimeter
    float perimeter = distance + height + hypotenuse;

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

    //get keypad keypress
    char key = keypad.getKey();
    int state = int(key);

    //button click and logic
    //initialize

    
    if (state == 0 and button == 50) {
      if (currentMillis - previousMillis >= interval) {
        previousMillis = currentMillis;
        const float rad = 0.01745329252;
        float sinx = sin(EEPROM.get(0, ang) * rad);
        float cosx = cos(EEPROM.get(0, ang) * rad);
        float tanx = tan(EEPROM.get(0, ang) * rad);
        float cscx = 1 / sinx;
        float secx = 1 / cosx;
        float cotx = 1 / tanx;

  //area of triangle
  float area = 0.5 * (EEPROM.get(1, distance) * EEPROM.get(2, height));


  if (ang == 0) {
    //initialize lcd
    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(WHITE);

    //group 1 display
    display.setCursor(0, 0);
    display.write(223);  //alpha symbol
    display.print(": " + String(EEPROM.get(0, ang)));
    display.setCursor(0, 8);
    display.write(224);  //beta symbol
    display.print(": " + String(90 - abs(EEPROM.get(0, ang))));
    display.setCursor(0, 16);
    display.print("a: 0.0");

    //group 2 display
    display.setCursor(68, 0);
    display.print("A: 0.0");
    display.setCursor(68, 8);
    display.print("B: " + String(EEPROM.get(1, distance), 1));
    display.setCursor(68, 16);
    display.println("C: " + String(EEPROM.get(3, hypotenuse), 1));

    display.setCursor(0, 24);
    display.print("---------------------");

    //degree display
    display.setCursor(0, 32);
    display.print("deg: " + String(EEPROM.get(0, ang)));

    //sins
    display.setCursor(0, 40);
    display.print("sin: " + String(sinx, 2));
    display.setCursor(68, 40);
    display.print("csc: UNDEF");

    //cosines
    display.setCursor(0, 48);
    display.print("cos: " + String(cosx, 2));
    display.setCursor(68, 48);
    display.print("sec: " + String(secx, 2));

    //tans
    display.setCursor(0, 56);
    display.print("tan: " + String(tanx, 2));
    display.setCursor(68, 56);
    display.print("cot: UNDEF");
  }

  else {
    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(WHITE);

    //group 1 display
    display.setCursor(0, 0);
    display.write(223);  //alpha symbol
    display.print(": " + String(EEPROM.get(0, ang)));
    display.setCursor(0, 8);
    display.write(224);  //beta symbol
    display.print(": " + String(90 - abs(EEPROM.get(0, ang))));
    display.setCursor(0, 16);
    display.print("a: " + String(area, 1));

    //group 2 display
    display.setCursor(68, 0);
    display.print("A: " + String(EEPROM.get(2, height), 1));
    display.setCursor(68, 8);
    display.print("B: " + String(EEPROM.get(1, distance), 1));
    display.setCursor(68, 16);
    display.println("C: " + String(EEPROM.get(3, hypotenuse), 1));

    display.setCursor(0, 24);
    display.print("---------------------");

    //degree display
    display.setCursor(0, 32);
    display.print("deg: " + String(EEPROM.get(0, ang)));

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
    display.print("tan: " + String(tanx, 2));
    display.setCursor(68, 56);
    display.print("cot: " + String(cotx, 2));
  }

  //radian conversion
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
  }

  // radian conversion for 0, 0 means constant
  else if (ang == 0) {
    display.setCursor(68, 32);
    display.print("rad: 0");
  }

  // radian conversion for positive angle
  else {
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
}


//measure values
void measure_diplayZeroValue(int ang, float distance, float hypotenuse, float sinx, float cosx, float secx, float tanx) {

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
  display.print(": " + String(90 - abs(ang)));
  display.setCursor(0, 16);
  display.print("a: 0.0");

  //group 2 display
  display.setCursor(68, 0);
  display.print("A: 0.0");
  display.setCursor(68, 8);
  display.print("B: " + String(distance, 1));
  display.setCursor(68, 16);
  display.println("C: " + String(hypotenuse, 1));

  display.setCursor(0, 24);
  display.print("---------------------");

  //degree display
  display.setCursor(0, 32);
  display.print("deg: " + String(ang));

  //sins
  display.setCursor(0, 40);
  display.print("sin: " + String(sinx, 2));
  display.setCursor(68, 40);
  display.print("csc: UNDEF");

  //cosines
  display.setCursor(0, 48);
  display.print("cos: " + String(cosx, 2));
  display.setCursor(68, 48);
  display.print("sec: " + String(secx, 2));

  //tans
  display.setCursor(0, 56);
  display.print("tan: " + String(tanx, 2));
  display.setCursor(68, 56);
  display.print("cot: UNDEF");
}

void measure_displayRadianConversion(int ang, int numerator, int denominator) {
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
  }

  // radian conversion for 0, 0 means constant
  else if (ang == 0) {
    display.setCursor(68, 32);
    display.print("rad: 0");
  }

  // radian conversion for positive angle
  else {
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
}

void measure_displayNonZeroValue(int ang, float distance, float height, float hypotenuse, float sinx, float cscx, float cosx, float secx, float tanx, float cotx, float area) {
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);

  //group 1 display
  display.setCursor(0, 0);
  display.write(223);  //alpha symbol
  display.print(": " + String(ang));
  display.setCursor(0, 8);
  display.write(224);  //beta symbol
  display.print(": " + String(90 - abs(ang)));
  display.setCursor(0, 16);
  display.print("a: " + String(area, 1));

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
  display.print("tan: " + String(tanx, 2));
  display.setCursor(68, 56);
  display.print("cot: " + String(cotx, 2));
        if (ang == 0) {
          measure_diplayZeroValue(ang, distance, hypotenuse, sinx, cosx, secx, tanx, cotx, area);
          measure_displayRadianConversion(ang, numerator, denominator);
        }
        //non zero values
        else {
          measure_displayNonZeroValue(ang, distance, height, hypotenuse, sinx, cscx, cosx, secx, tanx, cotx, area);
          measure_displayRadianConversion(ang, numerator, denominator);
        }
      }
    }

    //button 1 pressed
    if (state == 49) {
      if (button == 50) {
        button = 49;
        paused = true;
        EEPROM.put(0, ang);
        EEPROM.put(1, distance);
        EEPROM.put(2, height);
        EEPROM.put(3, hypotenuse);
        EEPROM.put(4, numerator);
        EEPROM.put(5, denominator);
        EEPROM.put(6, perimeter);
        save_measurements(ang, distance, height, hypotenuse, numerator, denominator);
      } 
      else if (button == 51) {
        button = 51;
        paused = true;
        convert_saveMeasurement(ang, distance, height, perimeter);
      }
    }

    //button 2 pressed
    else if (state == 50) {
      if (button == 49) {
        button = 50;
        if (ang == 0) {
          measure_diplayZeroValue(ang, distance, hypotenuse, sinx, cosx, secx, tanx);
          measure_displayRadianConversion(ang, numerator, denominator);
        }

        //non zero values
        else {
          measure_displayNonZeroValue(ang, distance, height, hypotenuse, sinx, cscx, cosx, secx, tanx, cotx, area);
          measure_displayRadianConversion(ang, numerator, denominator);
        }
      } else if (button == 51) {
        button = 50;
        if (ang == 0) {
          measure_diplayZeroValue(ang, distance, hypotenuse, sinx, cosx, secx, tanx);
          measure_displayRadianConversion(ang, numerator, denominator);
        }
        //non zero values
        else {
          measure_displayNonZeroValue(ang, distance, height, hypotenuse, sinx, cscx, cosx, secx, tanx, cotx, area);
          measure_displayRadianConversion(ang, numerator, denominator);
        }
      }
    }


    //button 3 pressed
    else if (state == 51) {
      if (button == 49) {
        button = 51;
        paused = true;
        //convert_saveMeasurement(ang, distance, height, perimeter);

      } else if (button == 50) {
        button = 51;
        //convert_measurements(ang, distance, height, area, perimeter);

      } else if (button == 51) {
        if (paused) {
          button = 49;
         // save_measurements(ang, distance, height, hypotenuse, numerator, denominator);

        } else {
          button = 50;
          paused = false;
          if (ang == 0) {
            measure_diplayZeroValue(ang, distance, hypotenuse, sinx, cosx, secx, tanx);
            measure_displayRadianConversion(ang, numerator, denominator);
          }

          //non zero values
          else {
            measure_displayNonZeroValue(ang, distance, height, hypotenuse, sinx, cscx, cosx, secx, tanx, cotx, area);
            measure_displayRadianConversion(ang, numerator, denominator);
          }
        }
      }
    }

    //if no button is clicked, loop and run through

    if (button == 49) {
      if (state == 50) {
        button == 50;
        if (ang == 0) {
          measure_diplayZeroValue(ang, distance, hypotenuse, sinx, cosx, secx, tanx);
          measure_displayRadianConversion(ang, numerator, denominator);
        }

        //non zero values
        else {
          measure_displayNonZeroValue(ang, distance, height, hypotenuse, sinx, cscx, cosx, secx, tanx, cotx, area);
          measure_displayRadianConversion(ang, numerator, denominator);
        }
      } else if (state == 51) {
        button == 51;
        //save_measurements(ang, distance, height, hypotenuse, numerator, denominator);
      }
    }

    else if (button == 50) {
      if (currentMillis - previousMillis >= interval) {
        previousMillis = currentMillis;
        if (ang == 0) {
          measure_diplayZeroValue(ang, distance, hypotenuse, sinx, cosx, secx, tanx);
          measure_displayRadianConversion(ang, numerator, denominator);
        }

        //non zero values
        else {
          measure_displayNonZeroValue(ang, distance, height, hypotenuse, sinx, cscx, cosx, secx, tanx, cotx, area);
          measure_displayRadianConversion(ang, numerator, denominator);
        }
      }
      paused = false;
    }

    else if (button == 51 and paused == false) {
      if (currentMillis - previousMillis >= interval) {
        previousMillis = currentMillis;
        convert_measurements(ang, distance, height, area, perimeter);
      }
    }
  }

  //writing the servo with no delay
  myservo.write(val);
  delay(15);

  //oled refresh
  display.display();
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


//save measurements
/*
void save_measurements(int ang, float distance, float height, float hypotenuse, int numerator, int denominator) {
  const float rad = 0.01745329252;
  float sinx = sin(EEPROM.get(0, ang) * rad);
  float cosx = cos(EEPROM.get(0, ang) * rad);
  float tanx = tan(EEPROM.get(0, ang) * rad);
  float cscx = 1 / sinx;
  float secx = 1 / cosx;
  float cotx = 1 / tanx;

  //area of triangle
  float area = 0.5 * (EEPROM.get(1, distance) * EEPROM.get(2, height));


  if (ang == 0) {
    //initialize lcd
    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(WHITE);

    //group 1 display
    display.setCursor(0, 0);
    display.write(223);  //alpha symbol
    display.print(": " + String(EEPROM.get(0, ang)));
    display.setCursor(0, 8);
    display.write(224);  //beta symbol
    display.print(": " + String(90 - abs(EEPROM.get(0, ang))));
    display.setCursor(0, 16);
    display.print("a: 0.0");

    //group 2 display
    display.setCursor(68, 0);
    display.print("A: 0.0");
    display.setCursor(68, 8);
    display.print("B: " + String(EEPROM.get(1, distance), 1));
    display.setCursor(68, 16);
    display.println("C: " + String(EEPROM.get(3, hypotenuse), 1));

    display.setCursor(0, 24);
    display.print("---------------------");

    //degree display
    display.setCursor(0, 32);
    display.print("deg: " + String(EEPROM.get(0, ang)));

    //sins
    display.setCursor(0, 40);
    display.print("sin: " + String(sinx, 2));
    display.setCursor(68, 40);
    display.print("csc: UNDEF");

    //cosines
    display.setCursor(0, 48);
    display.print("cos: " + String(cosx, 2));
    display.setCursor(68, 48);
    display.print("sec: " + String(secx, 2));

    //tans
    display.setCursor(0, 56);
    display.print("tan: " + String(tanx, 2));
    display.setCursor(68, 56);
    display.print("cot: UNDEF");
  }

  else {
    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(WHITE);

    //group 1 display
    display.setCursor(0, 0);
    display.write(223);  //alpha symbol
    display.print(": " + String(EEPROM.get(0, ang)));
    display.setCursor(0, 8);
    display.write(224);  //beta symbol
    display.print(": " + String(90 - abs(EEPROM.get(0, ang))));
    display.setCursor(0, 16);
    display.print("a: " + String(area, 1));

    //group 2 display
    display.setCursor(68, 0);
    display.print("A: " + String(EEPROM.get(2, height), 1));
    display.setCursor(68, 8);
    display.print("B: " + String(EEPROM.get(1, distance), 1));
    display.setCursor(68, 16);
    display.println("C: " + String(EEPROM.get(3, hypotenuse), 1));

    display.setCursor(0, 24);
    display.print("---------------------");

    //degree display
    display.setCursor(0, 32);
    display.print("deg: " + String(EEPROM.get(0, ang)));

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
    display.print("tan: " + String(tanx, 2));
    display.setCursor(68, 56);
    display.print("cot: " + String(cotx, 2));
  }

  //radian conversion
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
  }

  // radian conversion for 0, 0 means constant
  else if (ang == 0) {
    display.setCursor(68, 32);
    display.print("rad: 0");
  }

  // radian conversion for positive angle
  else {
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
}
*/

//measure values
void measure_diplayZeroValue(int ang, float distance, float hypotenuse, float sinx, float cosx, float secx, float tanx) {

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
  display.print(": " + String(90 - abs(ang)));
  display.setCursor(0, 16);
  display.print("a: 0.0");

  //group 2 display
  display.setCursor(68, 0);
  display.print("A: 0.0");
  display.setCursor(68, 8);
  display.print("B: " + String(distance, 1));
  display.setCursor(68, 16);
  display.println("C: " + String(hypotenuse, 1));

  display.setCursor(0, 24);
  display.print("---------------------");

  //degree display
  display.setCursor(0, 32);
  display.print("deg: " + String(ang));

  //sins
  display.setCursor(0, 40);
  display.print("sin: " + String(sinx, 2));
  display.setCursor(68, 40);
  display.print("csc: UNDEF");

  //cosines
  display.setCursor(0, 48);
  display.print("cos: " + String(cosx, 2));
  display.setCursor(68, 48);
  display.print("sec: " + String(secx, 2));

  //tans
  display.setCursor(0, 56);
  display.print("tan: " + String(tanx, 2));
  display.setCursor(68, 56);
  display.print("cot: UNDEF");
}

void measure_displayRadianConversion(int ang, int numerator, int denominator) {
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
  }

  // radian conversion for 0, 0 means constant
  else if (ang == 0) {
    display.setCursor(68, 32);
    display.print("rad: 0");
  }

  // radian conversion for positive angle
  else {
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
}

void measure_displayNonZeroValue(int ang, float distance, float height, float hypotenuse, float sinx, float cscx, float cosx, float secx, float tanx, float cotx, float area) {
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);

  //group 1 display
  display.setCursor(0, 0);
  display.write(223);  //alpha symbol
  display.print(": " + String(ang));
  display.setCursor(0, 8);
  display.write(224);  //beta symbol
  display.print(": " + String(90 - abs(ang)));
  display.setCursor(0, 16);
  display.print("a: " + String(area, 1));

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
  display.print("tan: " + String(tanx, 2));
  display.setCursor(68, 56);
  display.print("cot: " + String(cotx, 2));
}


//convert_page measurements
void convert_measurements(int ang, float distance, float height, float area, float perimeter) {
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);

  display.setCursor(20, 0);
  display.print("DISTANCE");
  display.setCursor(82, 0);
  display.print("HEIGHT");


  display.setCursor(0, 8);
  display.print("====================");
  display.setCursor(0, 16);
  display.print("cm");
  display.setCursor(2, 24);
  display.print("m");
  display.setCursor(0, 32);
  display.print("in");
  display.setCursor(0, 40);
  display.print("ft");
  display.setCursor(2, 48);
  display.print("a");
  display.setCursor(2, 56);
  display.print("p");

  //distance
  display.setCursor(28, 16);
  display.print(String(distance, 1));
  display.setCursor(28, 24);
  display.print(String(distance / 100, 1));
  display.setCursor(28, 32);
  display.print(String(distance / 2.54, 1));
  display.setCursor(28, 40);
  display.print(String(distance / 30.48, 1));
  display.setCursor(28, 48);
  display.print(String(area / 100, 1) + "m");
  display.setCursor(28, 56);
  display.print(String(perimeter / 100, 1) + "m");


  //height
  display.setCursor(84, 16);
  display.print(String(height, 1));
  display.setCursor(84, 24);
  display.print(String(height / 100, 1));
  display.setCursor(84, 32);
  display.print(String(height / 2.54, 1));
  display.setCursor(84, 40);
  display.print(String(height / 30.48, 1));


  display.display();
}

//convert_page save measurements

void convert_saveMeasurement(int ang, float distance, float height, float perimeter) {

  float hypotenuse = sqrt(pow(EEPROM.get(2, height), 2) + pow(EEPROM.get(1, distance), 2));
  float area = 0.5 * (EEPROM.get(1, distance) * EEPROM.get(2, height));

  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);

  display.setCursor(20, 0);
  display.print("DISTANCE");
  display.setCursor(82, 0);
  display.print("HEIGHT");


  display.setCursor(0, 8);
  display.print("====================");
  display.setCursor(0, 16);
  display.print("cm");
  display.setCursor(2, 24);
  display.print("m");
  display.setCursor(0, 32);
  display.print("in");
  display.setCursor(0, 40);
  display.print("ft");
  display.setCursor(2, 48);
  display.print("a");
  display.setCursor(2, 56);
  display.print("p");

  //distance
  display.setCursor(28, 16);
  display.print(String(EEPROM.get(1, distance), 1));
  display.setCursor(28, 24);
  display.print(String(EEPROM.get(1, distance) / 100, 1));
  display.setCursor(28, 32);
  display.print(String(EEPROM.get(1, distance) / 2.54, 1));
  display.setCursor(28, 40);
  display.print(String(EEPROM.get(1, distance) / 30.48, 1));
  display.setCursor(28, 48);
  display.print(String(area / 100, 1));
  display.setCursor(28, 56);
  display.print(String(EEPROM.get(6, perimeter) / 100, 1));


  //height
  display.setCursor(84, 16);
  display.print(String(EEPROM.get(2, height), 1));
  display.setCursor(84, 24);
  display.print(String(EEPROM.get(2, height) / 100, 1));
  display.setCursor(84, 32);
  display.print(String(EEPROM.get(2, height) / 2.54, 1));
  display.setCursor(84, 40);
  display.print(String(EEPROM.get(2, height) / 30.48, 1));


  display.display();
}
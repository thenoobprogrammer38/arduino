#include <Wire.h>
#include <Adafruit_GFX.h>
#include "Adafruit_SH1106.h"

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
#define OLED_RESET -1
Adafruit_SH1106 display(OLED_RESET);

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  display.begin(SH1106_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();
}

void loop() {
  float height = 88.3;
  float distance = 153;
  float area = 0.5 * (height * distance);
  float perimeter = height + distance + 176.7;

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
  display.print(String(area / 100, 1) + " m");
  display.setCursor(28, 56);
  display.print(String(perimeter / 100, 1) + " m");


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




  display.display();
}
#include <Wire.h>
#include <LiquidCrystal_I2C.h>



// Create two instances of the LiquidCrystal_I2C class
LiquidCrystal_I2C lcd1(0x26, 16, 2);
LiquidCrystal_I2C lcd2(0x27, 20, 4);

void setup() {
  // Initialize both LCD displays
  lcd1.init();
  lcd2.init();

  // Set up any initial display settings if needed
  lcd1.backlight();
  lcd2.backlight();

  // Display initial messages on each LCD
  lcd1.setCursor(0, 0);
  lcd1.print("LCD 1");
  lcd2.setCursor(0, 0);
  lcd2.print("LCD 2");
}

void loop() {
  // Continuously update the LCD displays if needed
  // You can perform different actions on each LCD
  
  lcd1.setCursor(0, 1);
  lcd1.print("Hello from LCD 1!");

  lcd2.setCursor(0, 1);
  lcd2.print("Hello from LCD 2!");

  delay(1000);
}

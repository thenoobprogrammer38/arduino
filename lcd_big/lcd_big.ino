#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Initialize the LCD object
LiquidCrystal_I2C lcd(0x27, 20, 4); // 0x27 is the default I2C address for the LCD module

void setup() {
  lcd.init();
  // Turn on the backlight
  lcd.setBacklight(HIGH);

  lcd.setCursor(0, 0);
  lcd.print("TRIGONOMETRIC RATIOS");
  lcd.setCursor(0, 1);
  lcd.print("s. in: ");
  lcd.setCursor(4, 1);
  lcd.print("-90.7");
  lcd.setCursor(0, 2);
  lcd.print("cos: ");
  lcd.setCursor(0, 3);
  lcd.print("tan: ");

  lcd.setCursor(10, 1);
  lcd.print("csc: ");
  lcd.setCursor(10, 2);
  lcd.print("sec: ");
  lcd.setCursor(10, 3);
  lcd.print("cot: ");
}

void loop() {
  
}

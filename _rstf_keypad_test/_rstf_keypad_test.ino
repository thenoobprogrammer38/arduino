#include <Keypad.h>

const byte ROWS = 1; // 1 row
const byte COLS = 3; // 3 columns

char keys[ROWS][COLS] = {
  {'1', '2', '3'}
};

byte rowPins[ROWS] = {2}; // Connect the row pin(s) to the specified pins
byte colPins[COLS] = {3, 4, 5}; // Connect the column pin(s) to the specified pins

Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

void setup() {
  Serial.begin(9600);
}

void loop() {
  char key = keypad.getKey();
  
  if (String(key) == "1") {
    Serial.println("measure");
  } 
  else if (String(key) == "2") {
    Serial.println("reset");
  } 
  else if (String(key) == "3") {
    Serial.println("next page");
  }
}
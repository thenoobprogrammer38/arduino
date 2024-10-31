#include <Keypad.h>
#include <EEPROM.h>

const byte ROWS = 1; 
const byte COLS = 3; 

char keys[ROWS][COLS] = {
  {'1', '2', '3'}
};

byte rowPins[ROWS] = {2}; 
byte colPins[COLS] = {3, 4, 5};

Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

float measured = 12345.67;
float reset = 0.0;

void setup() {
  Serial.begin(9600);
}

void loop() {
  char key = keypad.getKey();
  
  if (String(key) == "1") {
    EEPROM.put(0, measured);    
    Serial.print("measure: ");
    Serial.println(EEPROM.get(0, measured));
  } 
  else if (String(key) == "2") {
    EEPROM.put(1, reset);  
    Serial.print("reset: ");
    Serial.println(EEPROM.get(1, reset));
  } 
  else if (String(key) == "3") {
    Serial.println("next page");
  }
}

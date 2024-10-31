#include <Keypad.h>
#include <EEPROM.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

const byte ROWS = 1;
const byte COLS = 3;

char keys[ROWS][COLS] = {
  { '1', '2', '3' }
};

byte rowPins[ROWS] = { 2 };
byte colPins[COLS] = { 3, 4, 5 };

Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

LiquidCrystal_I2C lcd(0x27, 20, 4);

const int trigPin = 9;
const int echoPin = 10;

unsigned long previousMillis = 0;
const unsigned long interval = 1000;

long duration;
int distance;

int button = 50;
bool paused = false;

void setup() {
  Serial.begin(9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  lcd.init();
  lcd.setBacklight(HIGH);
}


void save(int distance) {
  lcd.clear();
  lcd.print("SAVE TRIANGLES");
  lcd.setCursor(0, 2);
  lcd.print(String(EEPROM.get(0, distance)));
}


void measure(int distance) {
  lcd.clear();
  lcd.print("MAIN TRIANGLES");
  lcd.setCursor(0, 2);
  lcd.print(distance);
}


void convert_pause(int distance) {
  lcd.clear();
  lcd.print("CONVERT: ");
  lcd.setCursor(0, 1);
  lcd.print(EEPROM.get(0, distance));
  lcd.setCursor(0, 2);
  lcd.print(String(EEPROM.get(0, distance) / 2.54) + " inches");
}


void convert_measure(int distance) {
  lcd.clear();
  lcd.print("CONVERT: ");
  lcd.setCursor(0, 1);
  lcd.print(distance);
  lcd.setCursor(0, 2);
  lcd.print(String(distance / 2.54) + " inches");
}



void loop() {

  unsigned long currentMillis = millis();

  char key = keypad.getKey();
  int state = int(key);


  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);

  distance = duration * 0.034 / 2;

  Serial.println(button);
  Serial.println(paused);

  //initialize
  if (state == 0 and button == 50) {
    if (currentMillis - previousMillis >= interval) {
      previousMillis = currentMillis;
      measure(distance);
    }
  }

  //button 1 pressed
  if (state == 49) {
    if (button == 50){
      button = 49;
      paused = true;
      EEPROM.put(0, distance);
      save(distance);
    }
    else if (button == 51){
      
      button = 51;
      paused = true;
      convert_pause(distance);
    }
  }

  //button 2 pressed
  else if (state == 50){
    if (button == 49){
      button = 50;
      measure(distance);
    }
    else if (button == 51){
      button = 50;
      measure(distance);
    }
  }


  //button 3 pressed
  else if (state == 51){
    if (button == 49){
      button = 51;
      paused = true;
      convert_pause(distance);
    }
    else if (button == 50){
      button = 51;
      convert_measure(distance);
    }
    else if (button == 51){
      if (paused){
        button = 49;
        save(distance);
      }
      else{
        button = 50;
        paused = false;
        measure(distance);
      }
    }
  }






  //if no button is clicked, loop and run through
  
  if (button == 49){
    if (state == 50){
      button == 50;
      measure(distance);
    }
    else if (state == 51){
      button == 51;
      save(distance);
    }
  }

  else if (button == 50) {
    if (currentMillis - previousMillis >= interval) {
      previousMillis = currentMillis;
      measure(distance);
    }
    paused = false;
  }

  else if (button == 51 and paused == false) {
    if (currentMillis - previousMillis >= interval) {
      previousMillis = currentMillis;
      convert_measure(distance);
    }
  }
}
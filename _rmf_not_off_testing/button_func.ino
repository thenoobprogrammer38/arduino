void saveMeasurements() {


}

void convertMeasurements(int ang, float distance, float height, float perimeter) {
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
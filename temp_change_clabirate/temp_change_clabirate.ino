#include <OneWire.h>
#include <DallasTemperature.h>


#define ONE_WIRE_BUS 2
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);
float temp_value;

float previousData;
float newData;


void setup() {
  Serial.begin(9600);
  sensors.begin();  //temp
}

void loop() {
  sensors.requestTemperatures();
  temp_value = sensors.getTempCByIndex(0);
  temp_value = temp_value + 0.5;  //calibrate

  Serial.println("Old: " + String(previousData));

  int diff = temp_value - previousData;
  previousData = temp_value;

  Serial.println("New: " + String(temp_value));

  Serial.println(temp_value);
  Serial.println("===============");
  Serial.println(diff);
  Serial.println("===============");

  delay(2000);
}

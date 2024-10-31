#include <math.h>

double degrees = 90;
double radians;

void setup() {
  Serial.begin(9600);
  
  radians = degrees * (3.14159265359 / 180.0);
  
  //Serial.print("Degrees: ");
  //Serial.println(degrees);
  //Serial.print("Radians: ");
  //Serial.println(radians, 6); // Specify the number of decimal places to display
  //Serial.println(sin(radians), 6);
  //Serial.print("hello");
}

void loop() {
  
}

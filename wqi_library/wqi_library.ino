#include "WQICalculator.h"

int main_temp_q_value;
int main_ph_q_value;
int main_turb_q_value;
int main_tds_q_value;

float temp_value = 23.7;
float ph_value = 8.1;
float turb_value = 25;
float tds_value = 136;

float main_wqi;
String main_classify;

void setup() {
  Serial.begin(9600);
}

void loop() {

  main_temp_q_value = tempQValue(temp_value);
  main_ph_q_value = phQValue(ph_value);
  main_turb_q_value = turbQValue(turb_value);
  main_tds_q_value = tdsQValue(tds_value);
  
  main_wqi = computeWQI(main_temp_q_value, main_ph_q_value, main_turb_q_value, main_tds_q_value);
  main_classify = classifyWQI (main_wqi);

  Serial.println(main_temp_q_value);
  Serial.println(main_ph_q_value);
  Serial.println(main_turb_q_value);
  Serial.println(main_tds_q_value);
  Serial.println(main_wqi);
  Serial.println(round(main_wqi));
  Serial.println(main_classify);


  Serial.println(); 
  delay(1000);
  Serial.println("===");
}
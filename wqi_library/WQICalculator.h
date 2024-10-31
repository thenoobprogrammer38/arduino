#include "WString.h"

//weighing values and variables
float temp_weight = 0.10;
float ph_weight = 0.11;
float turb_weight = 0.08;
float tds_weight = 0.07;

float temp_q_value;
float ph_q_value;
float turb_q_value;
float tds_q_value;

float computedWQI;


float tempQValue (float temp_value){
  if (temp_value == -10){temp_q_value = 55;} //point
  else if (temp_value > -10 && temp_value < 0){temp_q_value = 3.8 * temp_value + 93;}

  else if (temp_value == 0){temp_q_value = 93;} // point
  else if (temp_value > 0 && temp_value < 5){temp_q_value = -4 * temp_value + 93;}

  else if (temp_value == 5){temp_q_value = 73;} // point
  else if (temp_value > 5 && temp_value < 9.5){temp_q_value= -5.7778 * temp_value + 101.8889;;}

  else if (temp_value == 9.5){temp_q_value = 47;} // point
  else if (temp_value > 9.5 && temp_value < 12){temp_q_value= -4.4 * temp_value + 88.8;}

  else if (temp_value == 12){temp_q_value = 36;} // point
  else if (temp_value > 12 && temp_value < 14.5){temp_q_value= -1.6 * temp_value + 55.2;}

  else if (temp_value == 14.5){temp_q_value = 32;} // point
  else if (temp_value > 14.5 && temp_value < 21){temp_q_value= -1.8462 * temp_value + 58.7692;} 

  else if (temp_value == 21){temp_q_value = 20;} // point
  else if (temp_value > 21 && temp_value < 30){temp_q_value= -1.111109 * temp_value + 43.333297;} 
  
  else if (temp_value == 30){temp_q_value = 10;} // point
  else {temp_q_value = 0;} 

  return round (temp_q_value);
}

float phQValue (float ph_value){
  if (ph_value < 2){ph_q_value = 0;}
  else if (ph_value == 2){ph_q_value = 2;} //point
  else if (ph_value > 2 && ph_value < 3){ph_q_value = 2 * ph_value - 2;}

  else if (ph_value == 3){ph_q_value = 4;} //point
  else if (ph_value > 3 && ph_value < 3.5){ph_q_value = 4 * ph_value - 8;}
  
  else if (ph_value == 3.5){ph_q_value = 6;} //point
  else if (ph_value > 3.5 && ph_value < 4){ph_q_value = 6 * ph_value - 15;}

  else if (ph_value == 4){ph_q_value = 9;} //point
  else if (ph_value > 4 && ph_value < 4.1){ph_q_value = 10 * ph_value - 31;}
  
  else if (ph_value == 4.1){ph_q_value = 10;} //point
  else if (ph_value > 4.1 && ph_value < 4.5){ph_q_value = 12.5 * ph_value - 40.5;}

  else if (ph_value == 4.5){ph_q_value = 15;} //point
  else if (ph_value > 4.5 && ph_value < 4.8){ph_q_value = 16.67 * ph_value - 60;}

  else if (ph_value == 4.8){ph_q_value = 20;} //point
  else if (ph_value > 4.8 && ph_value < 5.1){ph_q_value = 33.333 * ph_value - 139.99;}

  else if (ph_value == 5.1){ph_q_value = 30;} //point
  else if (ph_value > 5.1 && ph_value < 6.2){ph_q_value = 27.2727 * ph_value - 108.6363;}

  else if (ph_value == 6.2){ph_q_value = 60;} //point
  else if (ph_value > 6.2 && ph_value < 6.8){ph_q_value = 38.3333 * ph_value - 177.6666;}

  else if (ph_value == 6.8){ph_q_value = 83;} //point
  else if (ph_value > 6.8 && ph_value < 7){ph_q_value = 25 * ph_value - 87;}

  else if (ph_value == 7){ph_q_value = 88;} //point
  else if (ph_value > 7 && ph_value < 7.1){ph_q_value = 20 * ph_value - 52;}

  else if (ph_value == 7.1){ph_q_value = 90;} //point
  else if (ph_value > 7.1 && ph_value < 7.2){ph_q_value = 20 * ph_value - 52;}

  else if (ph_value == 7.2){ph_q_value = 92;} //point
  else if (ph_value > 7.2 && ph_value < 7.4){ph_q_value = 5 * ph_value + 56;}

  else if (ph_value == 7.4){ph_q_value = 93;} //point
  else if (ph_value > 7.4 && ph_value < 7.6){ph_q_value = -5 * ph_value + 130;}

  else if (ph_value == 7.6){ph_q_value = 92;} //point
  else if (ph_value > 7.6 && ph_value < 7.8){ph_q_value = -10 * ph_value + 168;}

  else if (ph_value == 7.8){ph_q_value = 90;} //point
  else if (ph_value > 7.8 && ph_value < 8){ph_q_value = -30 * ph_value + 324;}

  else if (ph_value == 8){ph_q_value = 84;} //point
  else if (ph_value > 8 && ph_value < 8.9){ph_q_value = -35.56 * ph_value + 368.48;}

  else if (ph_value == 8.9){ph_q_value = 52;} //point
  else if (ph_value > 8.9 && ph_value < 9.7){ph_q_value = -32.5 * ph_value + 341.25;}

  else if (ph_value == 9.7){ph_q_value = 26;} //point
  else if (ph_value > 9.7 && ph_value < 10){ph_q_value = -20 * ph_value + 220;}

  else if (ph_value == 10){ph_q_value = 20;} //point
  else if (ph_value > 10 && ph_value < 10.3){ph_q_value = -16.67 * ph_value + 186.67;}

  else if (ph_value == 10.3){ph_q_value = 15;} //point
  else if (ph_value > 10.3 && ph_value < 10.7){ph_q_value = -10 * ph_value + 118;}

  else if (ph_value == 10.7){ph_q_value = 11;} //point
  else if (ph_value > 10.7 && ph_value < 10.8){ph_q_value = -10 * ph_value + 118;}

  else if (ph_value == 10.8){ph_q_value = 10;} //point
  else if (ph_value > 10.8 && ph_value < 11){ph_q_value = -10 * ph_value + 118;}

  else if (ph_value == 11){ph_q_value = 8;} //point
  else if (ph_value > 11 && ph_value < 11.5){ph_q_value = -6 * ph_value + 74;}

  else if (ph_value == 11.5){ph_q_value = 5;} //point
  else if (ph_value > 11.5 && ph_value < 12){ph_q_value = -4 * ph_value + 51;}

  else if (ph_value == 12){ph_q_value = 3;}
  else if (ph_value > 12){ph_q_value = 0;}

  return round (ph_q_value);
}

float turbQValue (float turb_value){
  if (turb_value == 0){turb_q_value = 99;}
  else if (turb_value > 0 && turb_value < 3){turb_q_value = -3 * turb_value + 99;}

  else if (turb_value == 3){turb_q_value = 90;}
  else if (turb_value > 3 && turb_value < 13){turb_q_value = -2 * turb_value + 96;}

  else if (turb_value == 13){turb_q_value = 70;}
  else if (turb_value > 13 && turb_value < 15){turb_q_value = -1.5 * turb_value + 89.5;}

  else if (turb_value == 15){turb_q_value = 67;}
  else if (turb_value > 15 && turb_value < 20){turb_q_value = -1.2 * turb_value + 85;}

  else if (turb_value == 20){turb_q_value = 61;}
  else if (turb_value > 20 && turb_value < 40){turb_q_value = -0.8 * turb_value + 77;}

  else if (turb_value == 40){turb_q_value = 45;}
  else if (turb_value > 40 && turb_value < 60){turb_q_value = -0.6 * turb_value + 69;}

  else if (turb_value == 60){turb_q_value = 33;}
  else if (turb_value > 60 && turb_value < 80 ){turb_q_value = -0.4 * turb_value + 57;}

  else if (turb_value == 80){turb_q_value = 25;}
  else if (turb_value > 80 && turb_value < 90 ){turb_q_value = -0.3 * turb_value + 49;}

  else if (turb_value == 90){turb_q_value = 22;}
  else if (turb_value > 90 && turb_value < 100 ){turb_q_value = -0.5 * turb_value + 67;}

  else if (turb_value == 100){turb_q_value = 17;}
  else if (turb_value > 100 ){turb_q_value = 0;}
  else {turb_q_value = 99;}

  return round (turb_q_value);
}

float tdsQValue (float tds_value){
  if (tds_value < 0){tds_q_value = 0;}
  else if (tds_value == 0){tds_q_value = 79;}
  else if (tds_value > 0 && tds_value < 10){tds_q_value = 0.3 * tds_value + 79;}

  else if (tds_value == 10){tds_q_value = 82;}
  else if (tds_value > 10 && tds_value < 20){tds_q_value = 0.2 * tds_value + 80;}

  else if (tds_value == 20){tds_q_value = 84;}
  else if (tds_value > 20 && tds_value < 30){tds_q_value = 0.05 * tds_value + 83;}

  else if (tds_value == 30){tds_q_value = 84.5;}
  else if (tds_value > 30 && tds_value < 40){tds_q_value = 0.15 * tds_value + 80;}

  else if (tds_value == 40){tds_q_value = 86;}
  else if (tds_value > 40 && tds_value < 60){tds_q_value = 0.05 * tds_value + 84;}

  else if (tds_value == 60){tds_q_value = 87;}
  else if (tds_value > 60 && tds_value < 70){tds_q_value = -0.1 * tds_value + 93;}

  else if (tds_value == 70){tds_q_value = 86;}
  else if (tds_value > 70 && tds_value < 150){tds_q_value = -0.0875 * tds_value + 92.125;}

  else if (tds_value == 150){tds_q_value = 79;}
  else if (tds_value > 150 && tds_value < 450){tds_q_value = -0.13 * tds_value + 98.5;}

  else if (tds_value == 450){tds_q_value = 40;}
  else if (tds_value > 450 && tds_value < 500){tds_q_value = -0.18 * tds_value + 121;}

  else if (tds_value == 500){tds_q_value = 31;}
  else if (tds_value > 500){tds_q_value = 0;}
  else {tds_value = 79;}

  return round (tds_q_value);
}

float computeWQI (float temp_q_value, float ph_q_value, float turb_q_value, float tds_q_value){
  computedWQI = ((temp_q_value * temp_weight) + (ph_q_value * ph_weight) + (turb_q_value * turb_weight) + (tds_q_value * tds_weight)) / (temp_weight + ph_weight + turb_weight + tds_weight);

  return computedWQI;
}

//Categorize WQI
String classifyWQI(float computedWQI){
  if (computedWQI >= 0 && computedWQI <= 25){return "VERY BAD";}
  else if (computedWQI > 25 && computedWQI <= 50){return "BAD";}
  else if (computedWQI > 50 && computedWQI <= 70){return "MEDIUM";}
  else if (computedWQI > 70 && computedWQI <= 90){return "GOOD";}
  else if (computedWQI > 90 && computedWQI <= 100){return "EXCELLENT";}

}
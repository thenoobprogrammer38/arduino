#define sensor_pin 34
int read_ADC;
int ntu;
 
void setup(){
  pinMode(sensor_pin, INPUT);
  Serial.begin(115200);
}
 
void loop(){  
  read_ADC = analogRead(sensor_pin);


  //208, 685
  Serial.println("Analog: " + String(read_ADC));
 // if(read_ADC>1555){
   // read_ADC=1555;
  //}

  ntu = map(read_ADC, 0, 4095, 300, 0) ;
  //int ntu2 = map(ntu, 0, 330, 300, 0);
  //if (ntu2 > 330) {ntu2 =  330;}
  //Serial.println(ntu2);

  //float voltage = ntu2 * ((3.3 / 4095.0) + 0.00408172472);

  Serial.println("Analog: " + String(read_ADC));
  //Serial.println("Volts: " + String(voltage));
  Serial.println(ntu);



  if(ntu < 10){
    Serial.println("Water Very Clean");
  }
  if(ntu >= 10 && ntu < 30){
    Serial.println("Water Norm Clean");
  }
  if(ntu>=30){
    Serial.println("Water Very Dirty");
  }

  Serial.println("============================");

  delay(200);
}
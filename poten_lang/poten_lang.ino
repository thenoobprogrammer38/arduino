
int potpin = 0;  // analog pin used to connect the potentiometer
int val;    // variable to read the value from the analog pin
 
void setup() {
  Serial.begin(9600);
}
 
void loop() {
  val = analogRead(potpin);            // reads the value of the potentiometer (value between 0 and 1023)
  val = map(val, 0, 1023, 0, 181);     // scale it to use it with the servo (value between 0 and 180)               // sets the servo position according to the scaled value
  Serial.println(val);
  delay(100);                           // waits for the servo to get there
  
}
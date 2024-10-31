const int pump = 3;

void setup() {
  pinMode(pump, OUTPUT);
}

void loop() {
  digitalWrite(pump, HIGH);
  delay(1000);
  
  digitalWrite(pump, LOW);
  delay(10000);

}

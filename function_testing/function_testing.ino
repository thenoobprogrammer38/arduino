const int trigPin = 9;
const int echoPin = 10;

float getDistance() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  long duration = pulseIn(echoPin, HIGH);
  float distance_cm = (duration / 2) / 29.1;
  
  return distance_cm;
}


void setup() {
  Serial.begin(9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
}

void display(float distance){
  Serial.println("Distance is: " + String(distance) + " cm");
}
void loop() {
  float dist = getDistance();
  display(dist);
  Serial.print("Distance: ");
  Serial.print(dist);
  Serial.println(" cm");
  delay(1000);
}

const int trigPin = 2;   // Trig pin of the ultrasonic sensor
const int echoPin = 3;   // Echo pin of the ultrasonic sensor

void setup() {
  Serial.begin(9600);
  
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
}

void loop() {
  // Clear the trigPin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  
  // Set the trigPin on HIGH state for 10 microseconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  // Read the echoPin, calculate the duration
  long duration = pulseIn(echoPin, HIGH);
  
  // Convert the duration to distance
  // Speed of sound in air is approximately 343 meters per second (or 0.0343 cm/microsecond)
  // The ultrasonic sensor measures the time taken by the sound to travel to the object and back
  // So, we divide the duration by 2 and multiply it by the speed of sound to get the distance in centimeters
  float distance = duration * 0.0343 / 2;
  
  // Print the distance on the serial monitor
  Serial.print("Distance: ");
  Serial.print(distance, 1);
  Serial.println(" cm");
  
  delay(1000);  // Delay between measurements
}

// Arduino code to convert degrees to radians in fraction form

void setup() {
  Serial.begin(9600);
}

void loop() {
  // Prompt for user input
  Serial.println("Enter the angle in degrees:");

  while (!Serial.available()) {
    // Wait for user input
  }

  // Read the input value
  int degrees = Serial.parseInt();

  // Convert degrees to radians
  float radians = degrees * 3.14159 / 180.0;

  // Calculate the fraction form
  int numerator = round(radians * 180.0 / 3.14159);
  int denominator = 180;

  // Find the greatest common divisor
  int gcd = findGCD(numerator, denominator);

  // Simplify the fraction
  numerator /= gcd;
  denominator /= gcd;

  // Print the result
  Serial.print("Radians: ");
  Serial.print(numerator);
  Serial.print("π/");
  Serial.println(denominator);

  // Wait for a moment before accepting new input
  delay(1000);
}

// Function to find the greatest common divisor (Euclidean algorithm)
int findGCD(int a, int b) {
  while (b != 0) {
    int temp = b;
    b = a % b;
    a = temp;
  }
  return a;
}

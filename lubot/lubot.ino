#include <esp8266_AT.h>
#include <SoftwareSerial.h>

// Define the ESP8266 TX and RX pins
SoftwareSerial esp8266(18, 19);

void setup() {
  // Open the Serial Monitor and wait for it to initialize
  Serial.begin(9600);
  while (!Serial);

  // Initialize the ESP8266 Serial communication
  esp8266.begin(115200);

  // Reset the ESP8266 module
  esp8266.println("AT+RST");
  delay(1000);

  // Set the WiFi mode to client
  esp8266.println("AT+CWMODE=1");
  delay(1000);

  // Connect to your WiFi network
  esp8266.println("AT+CWJAP=\"<WiFi-SSID>\",\"<WiFi-Password>\"");
  delay(5000);

  // Verify that the ESP8266 is connected to the internet
  esp8266.println("AT+CWJAP?");
  delay(1000);

  // Print the response from the ESP8266
  while (esp8266.available()) {
    Serial.write(esp8266.read());
  }
}

void loop() {
  // Add your code here to send and receive data over the internet
}

#include <MQ2.h>
#include <MQ135.h>
#include <esp8266_AT.h>
#include <SoftwareSerial.h>
#include <DHT.h>


// Define the ESP8266 TX and RX pins
SoftwareSerial esp8266(18, 19);

// Define the DHT22 pin
#define DHTPIN 2

// Initialize the DHT22 sensor
DHT dht(DHTPIN, DHT22);

// Define the MQ2 pin
#define SMOKE_PIN A1

// Define the MQ135 pin
#define AIR_QUALITY_PIN A0

// Define the server address and path
String serverAddress = 127.0.0.1;
String path = 


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
  esp8266.println("AT+CWJAP=\"<A11>\",\"<subtitle>\"");
  delay(5000);

  // Verify that the ESP8266 is connected to the internet
  esp8266.println("AT+CWJAP?");
  delay(1000);

  // Print the response from the ESP8266
  while (esp8266.available()) {
    Serial.write(esp8266.read());
  }

  // Initialize the DHT22 sensor
  dht.begin();
}

void loop() {
  // Measure temperature and humidity
  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();

  // Measure smoke
  float mq2_raw = mq2.readSmoke();

  // Measure air quality
  float mq135_ppm = mq135.getPPM();
  float aqi = map(mq135_ppm, 0, 1000, 0, 500); // map PPM to AQI range

  // Send data to the database via HTTP GET request
  String data = "AQI=" + String(AQI, 2) + "&Smoke=" + String(smoke, 2) + "&Temperature=" + String(temperature, 2) + "&Humidity=" + String(humidity, 2);
  String request = "POST " + path + " HTTP/1.1\r\n" +
                   "Host: " + serverAddress + "\r\n" +
                   "Content-Type: application/x-www-form-urlencoded\r\n" +
                   "Content-Length: " + String(data.length()) + "\r\n\r\n" +
                   data + "\r\n";

  esp8266.println("AT+CIPMUX=1");
  delay(1000);
  esp8266.println("AT+CIPSTART=0,\"TCP\",\"<Server-IP-Address>\",80");
  delay(1000);
  esp8266.print("AT+CIPSEND=0,");
  esp8266.println(url.length()+4);
  delay(1000);
  esp8266.print("GET ");
  esp8266.print(url);
  esp8266.println(" HTTP/1.1\r\nHost: <Server-IP-Address>\r\nConnection: close\r\n\r\n");
  delay(1000);
  esp8266.println("AT+CIPCLOSE=0");

  // Wait for 3 seconds before taking another measurement
  delay(3000);
}

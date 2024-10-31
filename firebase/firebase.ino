#include <Firebase.h>
#include <FirebaseArduino.h>
#include <FirebaseCloudMessaging.h>
#include <FirebaseError.h>
#include <FirebaseHttpClient.h>
#include <FirebaseObject.h>


//Firebase
#define FIREBASE_HOST "hydretsdatabase-default-rtdb.firebaseio.com"
#define FIREBASE_AUTH "npm0KjAQMxeu0ntgImxPizATtMlDpLTM9D1xzxqm"

#define WIFI_SSID "WifiniKohi"
#define WIFI_PASSWORD "koliekapay"


void setup(){
  Serial.begin(9600);

  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.println("Connecting");

  while (WiFi.status() != WL_CONNECTED) {
    Serial.println(".");
    delay(500);
  }
  Serial.println();
  Serial.print("Connected");
  Serial.print(WiFi.localIP());

  Firebase.begin (FIREBASE_HOST, FIREBASE_AUTH);
  delay(500);
}

void loop(){
  int ph = 7;
  int tds = 280;
  int temp = 32;
  int turb = 15;
  int wqi = 75;

  Firebase.setString("ph/phVal", String(ph));
  delay(300);
  Firebase.setString("tds/tdsVal", String(tds)); // corrected quote placement
  delay(300);
  Firebase.setString("temp/tempValue", String(temp));
  delay(300);
  Firebase.setString("turb/turbVal", String(turb));
  delay(300);
  Firebase.setString("wqi/wqiVal", String(wqi));
  delay(300);
}

#include <SoftwareSerial.h>

SoftwareSerial HM10(2, 3); // RX = 2, TX = 3

char appData;  

String inData = "";

void setup()

{

  Serial.begin(9600);

  Serial.println("HM10 serial started at 9600");

  HM10.begin(9600); // set HM10 serial at 9600 baud rate

  pinMode(13, OUTPUT); // onboard LED

  digitalWrite(13, LOW); // switch OFF LED
 


}


void loop()

{

  HM10.listen();  // listen the HM10 port

  while (HM10.available() > 0) {   // if HM10 sends something then read

    appData = HM10.read();

    inData = String(appData);  // save the data in string format

    Serial.write(appData);

  }


 

  if (Serial.available()) {           // Read user input if available.

    delay(10);

    HM10.write(Serial.read());

  }

  if ( inData == "0") {

    Serial.println("LED OFF");

    digitalWrite(13, LOW); // switch OFF LED

    delay(500);

  }

  if ( inData == "1") {

    Serial.println("LED ON");

    digitalWrite(13, HIGH); // switch ON LED

    delay(500);

    digitalWrite(13, HIGH); // switch ON LED

    delay(500);

    digitalWrite(13, LOW); // switch OFF LED

    delay(500);
    
    digitalWrite(13, HIGH); // switch ON LED

    delay(500);
    
    digitalWrite(13, LOW); // switch OFF LED

    delay(500);
    
    digitalWrite(13, HIGH); // switch ON LED

    delay(500);
    
    digitalWrite(13, LOW); // switch OFF LED

    delay(500);
    
    digitalWrite(13, HIGH); // switch ON LED

    delay(500);
    
    digitalWrite(13, LOW); // switch OFF LED

    delay(500);
    
    digitalWrite(13, HIGH); // switch OFF LED

    delay(500);

    

  }

}

//diplay text for angles equivalent to zero
void zeroAngle(int ang, float distance, float height, float hypotenuse, float sinx, float cosx, float secx, float tanx) {
  //initialize lcd
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);

  //group 1 display
  display.setCursor(0, 0);
  display.write(223);  //alpha symbol
  display.print(": " + String(ang));
  display.setCursor(0, 8);
  display.write(224);  //beta symbol
  display.print(": " + String(90 - abs(ang)));
  display.setCursor(0, 16);
  display.print("a: 0.0");

  //group 2 display
  display.setCursor(68, 0);
  display.print("A: 0.0");
  display.setCursor(68, 8);
  display.print("B: " + String(distance, 1));
  display.setCursor(68, 16);
  display.println("C: " + String(hypotenuse, 1));

  display.setCursor(0, 24);
  display.print("---------------------");

  //degree display
  display.setCursor(0, 32);
  display.print("deg: " + String(ang));



  //ratios display
  //sines
  display.setCursor(0, 40);
  display.print("sin: " + String(sinx, 2));
  display.setCursor(68, 40);
  display.print("csc: UNDEF");

  //cosines
  display.setCursor(0, 48);
  display.print("cos: " + String(cosx, 2));
  display.setCursor(68, 48);
  display.print("sec: " + String(secx, 2));

  //tans
  display.setCursor(0, 56);
  display.print("tan: " + String(tanx, 2));
  display.setCursor(68, 56);
  display.print("cot: UNDEF");
}

//display text for non zero angles
void notZeroAngle(int ang, float area, float height, float distance, float hypotenuse, float sinx, float cosx, float tanx, float cscx, float secx, float cotx) {
  //initialize lcd
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);

  //group 1 display
  display.setCursor(0, 0);
  display.write(223);  //alpha symbol
  display.print(": " + String(ang));
  display.setCursor(0, 8);
  display.write(224);  //beta symbol
  display.print(": " + String(90 - abs(ang)));
  display.setCursor(0, 16);
  display.print("a: " + String(area, 1));

  //group 2 display
  display.setCursor(68, 0);
  display.print("A: " + String(height, 1));
  display.setCursor(68, 8);
  display.print("B: " + String(distance, 1));
  display.setCursor(68, 16);
  display.println("C: " + String(hypotenuse, 1));

  display.setCursor(0, 24);
  display.print("---------------------");

  //degree display
  display.setCursor(0, 32);
  display.print("deg: " + String(ang));

  //ratios display
  //sines
  display.setCursor(0, 40);
  display.print("sin: " + String(sinx, 2));
  display.setCursor(68, 40);
  display.print("csc: " + String(cscx, 2));

  //cosines
  display.setCursor(0, 48);
  display.print("cos: " + String(cosx, 2));
  display.setCursor(68, 48);
  display.print("sec: " + String(secx, 2));

  //tans
  display.setCursor(0, 56);
  display.print("tan: " + String(tanx, 2));
  display.setCursor(68, 56);
  display.print("cot: " + String(cotx, 2));
}

//converting randian angle of measures
void radianAngle(int ang, int numerator, int denominator) {
  //negative angle radian conversion
  if (ang < 0) {
    if (numerator == 1) {
      display.setCursor(68, 32);
      display.print("r:-");
      display.write(226);  //pi symbol
      display.print("/" + String(denominator));
    } else {
      display.setCursor(68, 32);
      display.print("r:-" + String(numerator));
      display.write(226);  //pi symbol
      display.print("/" + String(denominator));
    }
  }
  // radian conversion for 0, 0 means constant
  else if (ang == 0) {
    display.setCursor(68, 32);
    display.print("rad: 0");
  }
  // radian conversion for positive angle
  else {
    if (numerator == 1) {
      display.setCursor(68, 32);
      display.print("r: ");
      display.write(226);  //pi symbol
      display.print("/" + String(denominator));
    } else {
      display.setCursor(68, 32);
      display.print("r: " + String(numerator));
      display.write(226);  //pi symbol
      display.print("/" + String(denominator));
    }
  }
}


//testing func
void test(int ang, float height, float distance, float hypotenuse) {
  Serial.println("Angle: " + String(ang));
  Serial.println("A:" + String(height, 1));
  Serial.println("B:" + String(distance, 1));
  Serial.println("C:" + String(hypotenuse, 1));
  Serial.println("========================\n");
}
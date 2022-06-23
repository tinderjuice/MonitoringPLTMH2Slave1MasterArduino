#include <SoftwareSerial.h>

SoftwareSerial Slave1(4, 5);

String inString1 = "", strData1 = "";
String ultra = "", lastString1 = "";
bool comComp1 = false, phars1 = false;
String distMM;

void setup() {
  Serial.begin(9600);
  Slave1.begin(9600);
}

void loop() {
  serialEvent1();
  pharsing();
  if (phars1 == true) {
    distMM = ultra.toFloat();
    inString1 = "";
    phars1 = false;
  }
  else {
    ultra = "";
  }
  Serial.println(distMM);
  delay(100);
}

void pharsing() {
  if (comComp1 == true) { //$ultra&{nilai ultrauensi}
    for (int j = 0; j < inString1.length(); j++) {
      if (inString1[j] == '&') {
        lastString1 = strData1;
        strData1 = "";
      }
      else if (inString1[j] == '$') {
        lastString1 = "";
      }
      else {
        if (lastString1 == "") {
          strData1 += inString1[j];
        }
        if (lastString1 == "ult") {
          ultra += inString1[j];
        }
      }
    }
    phars1 = true;
    comComp1 = false;
  }
}

void serialEvent1() {  //read slave 1
  while (Slave1.available()) {
    char inChar = (char)Slave1.read();
    inString1 += inChar;
    if (inChar == '\n') {
      comComp1 = true;
    }
  }
}

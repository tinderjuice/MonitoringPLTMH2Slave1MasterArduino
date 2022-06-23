#include “SoftwareSerial.h”

SoftwareSerial Slave1(2,3);
SoftwareSerial Slave2(7,8);

String inString1 = "", inString2 = "", strData1 = "", strData2 = "";
String TeganganR = "", TeganganS = "", TeganganT = "", arusR = "", arusS = "", arusT = "", frek = "", lastString1 = "", lastString2 = "";
bool comComp1 = false, comComp2 = false, phars1 = false, phars2 = false;
String voltR, voltS, voltT, ampereR, ampereS, ampereT, hz;

void setup() {
  Serial.begin(9600);
  Slave1.begin(9600);
  Slave2.begin(9600);
}

void loop() {
  serialEvent1();
  serialEvent2();
  pharsing();
  if (phars1 == true) {
    voltR = teganganR.toFloat();
    voltS = teganganS.toFloat();
    voltT = teganganT.toFloat();
    ampereR = arusR.toFloat();
    ampereS = arusS.toFloat();
    ampereT = arusT.toFloat();
    inString1 = "";
    phars1 = false;
  }
  else {
    teganganR = "";
    teganganS = "";
    teganganT = "";
    arusR = "";
    arusS = "";
    arusT = "";
  }
  if (phars2 == true) {
    hz = frek.toFloat();
    inString2 = "";
    phars2 = false;
  }
  else {
    frek = "";
  }
  Serial.print(voltR); Serial.print(":");
  Serial.print(voltS); Serial.print(":");
  Serial.print(voltT); Serial.print("\t:\t");
  Serial.print(ampereR); Serial.print(":");
  Serial.print(ampereS); Serial.print(":");
  Serial.print(ampereT); Serial.print("\t:\t");
  Serial.print(hz);
  delay(100);
}

void pharsing() {
  if (comComp1 == true) { //$vt&{nilai pembagi tegangan}$acs&{nilai arus}
    for (int i = 0; i < inString1.length(); i++) {
      if (inString1[i] == '&') {
        lastString1 = strData1;
        strData1 = "";
      }
      else if (inString1[i] == '$') {
        lastString1 = "";
      }
      else {
        if (lastString1 == "") {
          strData1 += inString1[i];
        }
        if (lastString1 == "vtR") {
          teganganR += inString1[i];
        if (lastString1 == "vtS") {
          teganganS += inString1[i];
        if (lastString1 == "vtT") {
          teganganT += inString1[i];
        }
        if (lastString1 == "acsR") {
          arusR += inString1[i];
        if (lastString1 == "acsS") {
          arusS += inString1[i];
        if (lastString1 == "acsT") {
          arusT += inString1[i];
        }
      }
    }
    phars1 = true;
    comComp1 = false;
  }

  if (comComp2 == true) { //$frek&{nilai frekuensi}
    for (int j = 0; j < inString2.length(); j++) {
      if (inString2[j] == '&') {
        lastString2 = strData2;
        strData2 = "";
      }
      else if (inString2[j] == '$') {
        lastString2 = "";
      }
      else {
        if (lastString2 == "") {
          strData2 += inString2[j];
        }
        if (lastString2 == "frek") {
          frek += inString2[j];
        }
      }
    }
    phars2 = true;
    comComp2 = false;
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

void serialEvent2() { //read slave 2
  while (Slave2.available()) {
    char inChar = (char)Slave2.read();
    inString2 += inChar;
    if (inChar == '\n') {
      comComp2 = true;
    }
  }
}

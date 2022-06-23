#include <SoftwareSerial.h>
#include <Ultrasonic.h>
SoftwareSerial Slave1(4, 5);

int distMM = 0;
unsigned long lastPrint = 0;

Ultrasonic ultrasonic(9, 10);

void setup() {
  Serial.begin(9600);
  Slave1.begin(9600);
  delay(100);
}

void loop() {
  distMM = ultrasonic.read();
  Serial.print(distMM);
  printData();
}

void printData() {
  if (millis() - lastPrint > 200) {
    Serial.println(distMM);
    Slave1.println();
    Slave1.print("$ult&"); Slave1.print(distMM);
    Slave1.println();
  }
}

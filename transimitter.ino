#include <SoftwareSerial.h>
SoftwareSerial loraSerial(2, 3);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  loraSerial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  loraSerial.println("Car is nearby");
  Serial.println("sending");
  delay(1000);
}
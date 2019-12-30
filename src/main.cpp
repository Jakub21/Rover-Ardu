#define BAUDRATE 9600
#define LED_PIN 13

#include <Arduino.h>

void setup() {
  // put your setup code here, to run once:
  pinMode(LED_PIN, OUTPUT);
  Serial.begin(BAUDRATE);
}

void loop() {
  // put your main code here, to run repeatedly:
  if (Serial.available()) {
    digitalWrite(LED_PIN, true);
    Serial.read();
  } else {
    digitalWrite(LED_PIN, false);
  }
}

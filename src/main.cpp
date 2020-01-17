/*
* Main.cpp for my rover project
* the code will probably be refactored
* currently I'm trying to create prototype
* which is somewhat functional
*/

#define BAUDRATE 115200
#define PIN_TMPR_RPI A1
#define PIN_TMPR_BAT A2
#define PIN_TMPR_CNV A3

#include <Arduino.h>

#define SERIALBUFF_CAPACITY 64
#define SERIALBUFF_CALL_MAX_LEN 16
#define SERIALBUFF_SEPARATOR ';'
#include "SerialBuffer.hpp"
SerialBuffer sBuffer;

#include "SerialTransmitter.hpp"
SerialTrasmitter sTransmitter;

/* UTILITY FUNCTIONS */

float mapval(float x, float ol, float oh, float nl, float nh) {
  float os = oh - ol;
  float ns = nh - nl;
  x -= ol;
  return (x / os * ns) + nl;
}
float analogToCelc(float x) { return mapval(x, 438, 572, 18, 35); }

/* FUNCTIONS CALLABLE FROM THE RASPBERRY */

void measureTemperature() {
  float tmpr = analogToCelc(analogRead(PIN_TMPR_RPI));
  sTransmitter.send(transmitKeys.TmprRaspberry, tmpr);
  tmpr = analogToCelc(analogRead(PIN_TMPR_BAT));
  sTransmitter.send(transmitKeys.TmprBattery, tmpr);
  tmpr = analogToCelc(analogRead(PIN_TMPR_CNV));
  sTransmitter.send(transmitKeys.TmprConverters, tmpr);
}

void setServoPositions(char base, char elbow, char wrist) {
  float baseAngle  = 360 * base / 256.0;
  sTransmitter.send(transmitKeys.ArmBase, baseAngle);
  float elbowAngle = 360 * base / 256.0;
  sTransmitter.send(transmitKeys.ArmElbow, elbowAngle);
  float wristAngle = 360 * base / 256.0;
  sTransmitter.send(transmitKeys.ArmWrist, wristAngle);
}

/* PROGRAM STRUCTURE */

void setup() {
  Serial.begin(BAUDRATE);
}

void execute() {
  // Execute stuff based on call contents
  int index = call[0];
  int arg0 = call[1], arg1 = call[2], arg2 = call[3], arg3 = call[4];
  switch(index) {
    case 0: measureTemperature(/*arg0, arg1, arg2,arg3*/); break;
    case 1: setServoPositions(arg0, arg1, arg2); break;
    default: sTransmitter.send(transmitKeys.Error);
  }
}

void loop() {
  if (sBuffer.readAvailable()) {
    sBuffer.readSerial();
  }
  if (sBuffer.callAvailable()) {
    sBuffer.nextCall();
    execute();
  }
}

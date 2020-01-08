#define BAUDRATE 115200

#include <Arduino.h>

#define SERIALBUFF_CAPACITY 64
#define SERIALBUFF_CALL_MAX_LEN 16
#define SERIALBUFF_SEPARATOR ';'
#include "SerialBuffer.hpp"
SerialBuffer sBuffer;

#include "SerialTransmitter.hpp"
SerialTrasmitter sTransmitter;

#define PIN_TMPR_1 5

float mapval(float x, float ol, float oh, float nl, float nh) {
  float os = oh - ol;
  float ns = nh - nl;
  x -= ol;
  return (x / os * ns) + nl;
}


/* FUNCTIONS CALLABLE FROM THE RASPBERRY */

void measureTemperature() {
  float tmprCelc = mapval(analogRead(PIN_TMPR_1), 438, 572, 18, 35);
  sTransmitter.send(transmitKeys.TmprRaspberry, tmprCelc);
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
    default: sTransmitter.transmit(transmitKeys.Error);
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

#ifndef SERIALBUFF_HPP
#define SERIALBUFF_HPP

#include "Queue.hpp"

char call[SERIALBUFF_CALL_MAX_LEN];
short int callLength = 0;

class SerialBuffer {
 private:
  Queue<char> queue = Queue<char>(SERIALBUFF_CAPACITY);

 public:
  SerialBuffer() {}
  // ~SerialBuffer() {delete &queue;}

  int readSerial() {
    // Reads from serial until it's empty
    int amount = 0;
    while (Serial.available()) {
      queue.push(Serial.read());
      amount++;
      delay(1);
    }
    return amount;
  }

  void nextCall() {
    // Pops next call from queue and puts it in global variable "call"
    int queueLength = queue.length();
    callLength = 0;
    while (true) {
      char current = queue.pop();
      if (current == SERIALBUFF_SEPARATOR) break;
      if (callLength >= queueLength || callLength >= SERIALBUFF_CALL_MAX_LEN) break;
      call[callLength] = current;
      callLength++;
    }
  }

  bool readAvailable() {
    // Checks if there is data ready to read from Serial
    return Serial.available() > 0;
  }

  bool callAvailable() {
    // Checks if there is data ready to be converted to call
    return queue.length() > 0 && queue.contains((char)';');
  }
};

#endif

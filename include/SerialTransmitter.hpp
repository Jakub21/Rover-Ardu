#ifndef SERIALTRANSMITTER_HPP
#define SERIALTRANSMITTER_HPP

struct TransmitKeys {
  int TmprRaspberry = 1, TmprBattery = 2, TmprConverters = 3,
  ArmBase = 10, ArmElbow = 11, ArmWrist = 12,
  Error = 100;
};
TransmitKeys transmitKeys;

class SerialTrasmitter {
 public:
  void send(int key, int value) {
    Serial.print(key);
    Serial.print(' ');
    Serial.println(value);
  }
  void send(int key, float value) {
    Serial.print(key);
    Serial.print(' ');
    Serial.println(value);
  }
  void send(int key) { Serial.println(key); }
};

#endif

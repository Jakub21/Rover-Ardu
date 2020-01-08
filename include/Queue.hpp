#ifndef QUEUE_HPP
#define QUEUE_HPP

// Constant size queue implementation

template <class Tpl>
class Queue {
 private:
  int size = 0;
  int tail = 0;
  Tpl elements[SERIALBUFF_CAPACITY];

  void shiftLeft(int amount) {
    for (int i = 0; i < tail; i++) elements[i] = elements[i + amount];
    tail -= amount;
  }

 public:
  Queue() {}
  Queue(Tpl fill) {
    for (int i = 0; i < SERIALBUFF_CAPACITY; i++) elements[i] = fill;
  }

  int push(Tpl elm) {
    // Add element to the queue
    elements[tail] = elm;
    tail++;
    return tail;
  }
  Tpl pop() {
    // Get element from the queue
    if (tail == 0) return Tpl();
    Tpl head = elements[0];
    shiftLeft(1);
    return head;
  }
  Tpl* getAll() {
    // Get all elements from the queue (and empty it)
    Tpl* result = new Tpl[tail];
    for (int i = 0; i < tail; i++) result[i] = elements[i];
    shiftLeft(tail);
    return result;
  }

  bool contains(Tpl what) {
    for (int i = 0; i < tail; i++) {
      if (elements[i] == what) return true;
    }
    return false;
  }

  int length() { return tail; }
  int maxLength() { return size; }

  void printSelf() {
    Serial.print("<Queue::printDebug> {\n");
    delay(15);
    Serial.print("  limit = ");
    delay(10);
    Serial.println(size);
    delay(10);
    Serial.print("  length = ");
    delay(10);
    Serial.println(tail);
    delay(10);

    for (int i = 0; i < tail; i++) {
      Serial.print("  ");
      delay(10);
      Serial.print(i);
      delay(10);
      Serial.print('\t');
      delay(10);
      Serial.println((int)elements[i]);
      delay(10);
    }
    Serial.println("}");
    delay(10);
  }
};

#endif

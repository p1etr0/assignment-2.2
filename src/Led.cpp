#include "Led.h"
#include "Arduino.h"

Led::Led(int pin) {
  this->pin = pin;
}

void Led::switchOn() {
  digitalWrite(pin, HIGH);
}

void Led::switchOff() {
  digitalWrite(pin, LOW);
};
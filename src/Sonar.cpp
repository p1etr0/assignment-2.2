#include "Sonar.h"
#include "Arduino.h"

Sonar::Sonar(int pinTrig, int pinEcho){
  this->pinTrig = pinTrig;
  this->pinEcho = pinEcho;
} 

float Sonar::getDistance(float temperature) {
    // non funziona la formula 
    float vs = 331.45 + 0.62 * temperature;

    digitalWrite(pinTrig, LOW);
    delayMicroseconds(2);

    digitalWrite(pinTrig, HIGH);
    delayMicroseconds(10);

    digitalWrite(pinTrig, LOW);

    unsigned long interval = pulseIn(pinEcho, HIGH, 30000);

    if (interval == 0) {
        return -1.0;
    }

    float time = interval / 1000000.0;

    float distance = (time * vs) / 2.0;

    return distance * 100.0; // centimetri
}

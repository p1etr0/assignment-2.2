#include "Sonar.h"
#include "Arduino.h"

Sonar::Sonar(int pinTrig, int pinEcho){
  this->pinTrig = pinTrig;
  this->pinEcho = pinEcho;
} 

float Sonar::getDistance(float temperature) {
    // non funziona la formula 
    /* Triggering stage: sending the impulse */
    float vs = 331.45 + 0.62*temperature;
    digitalWrite(pinTrig,LOW);
    delayMicroseconds(3);
    digitalWrite(pinTrig,HIGH);
    delayMicroseconds(5);
    digitalWrite(pinTrig,LOW);
    
    /* Receiving the echo */

    float tUS = pulseIn(pinEcho, HIGH);
    if (tUS > 0){
      float t = tUS / 1000.0 / 1000.0 / 2;
      float d = t*vs;
      return d;
    } else {
      return -1.0;
    }
}

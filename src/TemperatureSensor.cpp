#include "TemperatureSensor.h"
#include "Arduino.h"

TemperatureSensor::TemperatureSensor(int pin){
  this->pin = pin;
}

float TemperatureSensor::getTemperature(){
  // non funziona la formula porco giuda
    return (analogRead(pin)* 5 - 0.5)*100 ; // convert the analog reading to temperature in Celsius
}


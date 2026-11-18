#include "TemperatureSensor.h"
#include "Arduino.h"

TemperatureSensor::TemperatureSensor(int pin){
  this->pin = pin;
}

float TemperatureSensor::getTemperature(){
  return ((analogRead(pin)/1023.0*5.0*1000.0)-500)/10.0 ; // convert the analog reading to temperature in Celsius
}


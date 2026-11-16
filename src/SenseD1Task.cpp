#include "SenseD1Task.h"
#include "Arduino.h"

SenseD1Task::SenseD1Task(int pinTrig, int pinEcho, int pinTemp){
    this->pinTrig = pinTrig;
    this->pinEcho = pinEcho;
    this->pinTemp = pinTemp;
}
  
void SenseD1Task::init(int period){
    Task::init(period);
    tempSensor = new TemperatureSensor(pinTemp);    
    sonar = new Sonar(pinTrig, pinEcho);  
}
  
void SenseD1Task::tick(){
    float temperature = tempSensor->getTemperature();
    temperature = 20.0;
    float distance = sonar->getDistance(temperature);
    Serial.print("Temperature: " + String(temperature) + " | Distance: " + String(distance) + "\n");
}

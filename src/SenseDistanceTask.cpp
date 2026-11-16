#include "SenseDistanceTask.h"
#include "Arduino.h"

SenseDistanceTask::SenseDistanceTask(int pinTrig, int pinEcho, int pinTemp){
    this->pinTrig = pinTrig;
    this->pinEcho = pinEcho;
    this->pinTemp = pinTemp;
}
  
void SenseDistanceTask::init(int period){
    Task::init(period);
    tempSensor = new TemperatureSensor(pinTemp);    
    sonar = new Sonar(pinTrig, pinEcho);  
}
  
void SenseDistanceTask::tick(){
    float temperature = tempSensor->getTemperature();
    float distance = sonar->getDistance(temperature);
    
}

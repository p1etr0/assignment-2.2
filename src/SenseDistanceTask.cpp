#include "SenseDistanceTask.h"
#include "Context.h"
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
    
    if (Context::getInstance().isWorking() && distance > D1 && distance < D2){
        Context::getInstance().setPreAlarm();
    } else if (Context::getInstance().isPreAlarm()) {
        if (distance < D1) {
            Context::getInstance().setAlarm();
        } else if (distance > D2) {
            Context::getInstance().setWorking();
        }
    }

}

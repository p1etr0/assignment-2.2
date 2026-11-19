#include "SenseDistanceTask.h"
#include "Context.h"
#include "Arduino.h"

SenseDistanceTask::SenseDistanceTask(int pinTrig, int pinEcho, int pinTemp, int sectors){
    this->pinTrig = pinTrig;
    this->pinEcho = pinEcho;
    this->pinTemp = pinTemp;
    this->spaceMap = new float[sectors]{};
}
  
void SenseDistanceTask::init(int period){
    Task::init(period);
    tempSensor = new TemperatureSensor(pinTemp);    
    sonar = new Sonar(pinTrig, pinEcho);  
    lcd = new Lcd();
}
  
void SenseDistanceTask::tick(){
    float temperature = tempSensor->getTemperature();
    float distance = sonar->getDistance(temperature);
    Context& context = Context::getInstance();
    
    if (context.isWorking()){
        int currentSector = context.getCurrentSector();
        lcd->write(currentSector, spaceMapping(currentSector, distance));
        if (distance > D1 && distance < D2) {
        context.setPreAlarm();
        }
    } else if (context.isPreAlarm()) {
        lcd->clear();
        if (distance < D1) {
            context.setAlarm();
        } else if (distance > D2) {
            context.setWorking();
        }
    } else {
        lcd->clear();
    }
}

bool SenseDistanceTask::spaceMapping(int currentSector, float distance){
    if (spaceMap[currentSector] == 0) {
        spaceMap[currentSector] = distance;
        return false;
    } else if (spaceMap[currentSector] + TOLERANCE >= distance &&
                distance >= spaceMap[currentSector] - TOLERANCE) {
        return false;
    }

    return true;
}

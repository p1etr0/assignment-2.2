#include "SenseDistanceTask.h"
#include "Arduino.h"
#include "components/MsgService.h"
#include "Context.h"

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
    Context& context = Context::getInstance();
    temperature = tempSensor->getTemperature();
    distance = sonar->getDistance(temperature);

    switch (context.getState())
    {
    case WORKING:
        currentSector = context.getCurrentSector();
        objectDetected = spaceMapping(currentSector, distance);
        lcd->write(currentSector, objectDetected);
        Serial.println("rdr:"+String(currentSector)+"|"+(objectDetected?"True":"False")+"|"+String(distance));
        if (distance > D1 && distance < D2) {
            context.setPreAlarm();
        }
        break;
    case PRE_ALARM:
        lcd->clear();
        if (distance < D1) {
            context.setAlarm();
        } else if (distance > D2) {
            context.setWorking();
        }
        break;
    default:
        lcd->clear();
        break;
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

#ifndef __SENSEDISTANCETASK__
#define __SENSEDISTANCETASK__

#include "Task.h"
#include "TemperatureSensor.h"
#include "Sonar.h"

class SenseDistanceTask: public Task { 

public:
    SenseDistanceTask(int pinTrig, int pinEcho, int pinTemp);
    void init(int period);
    void tick();

private:
    TemperatureSensor* tempSensor;
    Sonar* sonar;
    int pinTrig;
    int pinEcho;
    int pinTemp;
};



#endif
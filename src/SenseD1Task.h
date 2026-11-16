#ifndef __SENSED1TASK__
#define __SENSED1TASK__

#include "Task.h"
#include "TemperatureSensor.h"
#include "Sonar.h"

class SenseD1Task: public Task { 

public:
    SenseD1Task(int pinTrig, int pinEcho, int pinTemp);
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
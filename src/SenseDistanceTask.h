#ifndef __SENSEDISTANCETASK__
#define __SENSEDISTANCETASK__

#include "Task.h"
#include "components/TemperatureSensor.h"
#include "components/Sonar.h"

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
    const int D1 = 1;
    const int D2 = 2;
};



#endif
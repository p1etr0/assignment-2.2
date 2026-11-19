#ifndef __SENSEDISTANCETASK__
#define __SENSEDISTANCETASK__

#include "Task.h"
#include "components/TemperatureSensor.h"
#include "components/Sonar.h"
#include "components/Lcd.h"

class SenseDistanceTask: public Task { 

public:
    SenseDistanceTask(int pinTrig, int pinEcho, int pinTemp, int sectors);
    void init(int period);
    void tick();
    bool spaceMapping(int currentSector, float distance);

private:
    TemperatureSensor* tempSensor;
    Sonar* sonar;
    Lcd* lcd;
    int pinTrig;
    int pinEcho;
    int pinTemp;
    float* spaceMap;
    const int D1 = 1;
    const int D2 = 2;
    const float TOLERANCE = 0.05;
};

#endif
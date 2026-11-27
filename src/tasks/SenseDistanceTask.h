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
    bool objectDetected;
    int pinTrig;
    int pinEcho;
    int pinTemp;
    int currentSector;
    float temperature;
    float distance;
    float* spaceMap;
    const float D1 = 0.20;
    const float D2 = 0.30;
    const float TOLERANCE = 0.05;
};

#endif
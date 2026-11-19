#ifndef __SWEEPTASK__
#define __SWEEPTASK__

#include "Task.h"
#include "components/ServoMotor.h"
#include "components/Potentiometer.h"
#include "components/Lcd.h"

class SweepTask: public Task { 

public:
    SweepTask(int pinServo, int pinPot, int sectors);
    void init(int period);
    void tick();

private:
    int pinServo;
    int pinPot;
    int sectors;
    int currentSector;
    const int S1 = 2; // moltiplicatore movimento WORKING
    const int S2 = 1; // // moltiplicatore movimento PRE_ALARM
    int periodS1; // periodo movimento WORKING
    int periodS2; // periodo movimento PRE_ALARM
    ServoMotor* servo;
    Potentiometer* pot;
};

#endif
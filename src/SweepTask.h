#ifndef __SWEEPTASK__
#define __SWEEPTASK__

#include "Task.h"
#include "ServoMotor.h"
#include "Potentiometer.h"

class SweepTask: public Task { 

public:
    SweepTask(int pinServo, int pinPot);
    void init(int period);
    void tick();

private:
    int pinServo;
    int pinPot;
    const int S1 = 2; // moltiplicatore movimento WORKING
    const int S2 = 1; // // moltiplicatore movimento PRE_ALARM
    
    ServoMotor* servo;
    Potentiometer* pot;
};

#endif
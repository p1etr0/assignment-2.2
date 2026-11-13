#ifndef __MANUALSWEEPTASK__
#define __MANUALSWEEPTASK__

#include "Task.h"
#include "ServoMotor.h"
#include "Potentiometer.h"

class ManualSweepTask: public Task { 

public:
    ManualSweepTask(int pinServo, int pinPot);
    void init(int period, int sectors);
    void tick();

private:
    ServoMotor* servo;
    Potentiometer* pot;
    int pinServo;
    int pinPot;
};



#endif
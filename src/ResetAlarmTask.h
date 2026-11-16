#ifndef __RESETALARMTASK__
#define __RESETALARMTASK__

#include "Task.h"
#include "ServoMotor.h"
#include "Led.h"

class ResetAlarmTask: public Task { 

public:
    ResetAlarmTask(int pinLed, int pinServo);
    void init(int period);
    void tick();

private:
    int pinLed;
    int pinServo;
    ServoMotor* servo;
    Led* led;
};

#endif
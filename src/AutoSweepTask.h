#ifndef __AUTOSWEEPTASK__
#define __AUTOSWEEPTASK__

#include "Task.h"
#include "ServoMotor.h"

class AutoSweepTask: public Task { 

public:
    AutoSweepTask(int pinServo);
    void init(int period, Context context);
    void tick();

private:
    int pinServo;
    ServoMotor* servo;
};

#endif
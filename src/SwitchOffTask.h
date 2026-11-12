#ifndef __SWITCHOFFTASK__
#define __SWITCHOFFTASK__

#include "Task.h"
#include "Led.h"

class SwitchOffTask: public Task { 

public:
    SwitchOffTask
(int pin);
    void init(int period);
    void tick();

private:
    int pin;
    Led* led;
    enum {ON, OFF} state;
};

#endif
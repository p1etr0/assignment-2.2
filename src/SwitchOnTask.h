#ifndef __SWITCHONTASK__
#define __SWITCHONTASK__

#include "Task.h"
#include "Led.h"

class SwitchOnTask: public Task { 

public:
    SwitchOnTask(int pin);
    void init();
    void tick();

private:
    int pin;
    Led* led;
    enum {ON, OFF} state;
};

#endif
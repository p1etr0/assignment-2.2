#ifndef __BLINKINGTASK__
#define __BLINKINGTASK__

#include "Task.h"
#include "Led.h"

class BlinkingTask: public Task { 

public:
    BlinkingTask(int pin);
    void init(int period);
    void tick();

private:
    int pin;
    Light* led;
    enum {ON, OFF} state;
};

#endif
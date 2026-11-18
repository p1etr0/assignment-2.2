#ifndef __LEDCONTROLTASK__
#define __LEDCONTROLTASK__

#include "Task.h"
#include "Led.h"

class LedControlTask: public Task { 

public:
    LedControlTask(int pinRed, int pinGreen);
    void init(int period);
    void tick();

private:
    int pinRed;
    int pinGreen;
    Led* greenLed;
    Led* redLed;
    enum {ON, OFF} redState, greenState;
};

#endif
#ifndef __SLEEPTASK__
#define __SLEEPTASK__

#include "Task.h"

class SleepTask: public Task { 

public:
    SleepTask();
    void init();
    void tick();

private:
};

#endif

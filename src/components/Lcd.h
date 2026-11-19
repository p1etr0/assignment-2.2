#ifndef __LCD__
#define __LCD__

#include "LiquidCrystal_I2C.h"

class Lcd { 

public:
    Lcd();
    void write(int currentSector, bool objectDetected);
    void clear();
private:
    LiquidCrystal_I2C* lcd;
};

#endif
#ifndef __SONAR__
#define __SONAR__

class Sonar {
 
public: 
    Sonar(int pinTrig, int pinEcho);
    float getDistance(float temperature);

private:
    int pinTrig;
    int pinEcho;
};

#endif
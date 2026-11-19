#ifndef __SERVO_MOTOR__
#define __SERVO_MOTOR__
#include "Arduino.h"
#include "ServoTimer2Plus.h"

class ServoMotor {

public:
    ServoMotor(int pin, int sectors);
    int sweep();
    void setPosition(int angle);

private:
  ServoTimer2Plus motor;
  int pin; 
  int sectorSpan;
  int position;
  int currentSector;
  enum direzione { FORWARD = 1, BACKWARD = -1 };
  direzione dir;
};

#endif
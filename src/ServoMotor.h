#ifndef __SERVO_MOTOR__
#define __SERVO_MOTOR__

#include "ServoTimer2.h"

class ServoMotor {

public:
    ServoMotor(int pin, int sectors);
    void sweep();
    void setPosition(int angle);

private:
  ServoTimer2 motor;
  int pin; 
  int sectors;
  int position;
  enum direzione { FORWARD = 1, BACKWARD = -1 };
  direzione dir;
};

#endif
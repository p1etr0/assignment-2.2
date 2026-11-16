#ifndef __SERVO_MOTOR__
#define __SERVO_MOTOR__
#include "Arduino.h"
#include "ServoTimer2Plus.h"

class ServoMotor {

public:
    ServoMotor(int pin, int sectors);
    void sweep();
    void setPosition(int angle);

private:
  ServoTimer2Plus motor;
  int pin; 
  int sectors;
  int position;
  enum direzione { FORWARD = 1, BACKWARD = -1 };
  direzione dir;
};

#endif
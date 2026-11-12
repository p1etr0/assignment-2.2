#ifndef __SERVO_MOTOR__
#define __SERVO_MOTOR__

class ServoMotor {

public:
    ServoMotor(int pin, int sectors);
    void on();
    bool getState();
    void setPosition(int angle);
    void off();

private:
  int pin; 
  bool isOn;
  int sectors;
};

#endif
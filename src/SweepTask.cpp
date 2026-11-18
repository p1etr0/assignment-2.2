#include "SweepTask.h"
#include "Context.h"
#include "Arduino.h"

SweepTask::SweepTask(int pinServo, int pinPot){
    this->pinServo = pinServo;
    this->pinPot = pinPot;
}
  
void SweepTask::init(int period){
    Task::init(period); 
    this->servo = new ServoMotor(pinServo, 10);
    this->pot = new Potentiometer(pinPot);
}

void SweepTask::tick(){

    if (Context::getInstance().isWorking()) {
        this->setPeriod(S1*getPeriod());
        servo->sweep();
    } else if (Context::getInstance().isPreAlarm()) {
        this->setPeriod(S2*getPeriod());
        servo->sweep();
    } else if (Context::getInstance().isAlarm()) {
        int angle = map(pot->getValue(), 0, 1023, 0, 180);
        servo->setPosition(angle);
    }
}
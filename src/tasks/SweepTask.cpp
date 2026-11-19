#include "SweepTask.h"
#include "Context.h"

SweepTask::SweepTask(int pinServo, int pinPot, int sectors){
    this->pinServo = pinServo;
    this->pinPot = pinPot;
    this->sectors = sectors;
    this->currentSector = 0;
}
  
void SweepTask::init(int period){
    Task::init(period); 
    this->servo = new ServoMotor(pinServo, sectors);
    this->pot = new Potentiometer(pinPot);
}

void SweepTask::tick(){
    if (Context::getInstance().isWorking()) {
        this->setPeriod(S1*getPeriod());
        currentSector = servo->sweep();
        Context::getInstance().setCurrentSector(currentSector);
    } else if (Context::getInstance().isPreAlarm()) {
        this->setPeriod(S2*getPeriod());
        servo->sweep();
    } else if (Context::getInstance().isAlarm()) {
        int angle = map(pot->getValue(), 0, 1023, 0, 180);
        servo->setPosition(angle);
    }
}
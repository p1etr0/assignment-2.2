#include "SweepTask.h"
#include "Context.h"

SweepTask::SweepTask(int pinServo, int pinPot, int sectors){
    this->pinServo = pinServo;
    this->pinPot = pinPot;
    this->sectors = sectors;
    this->currentSector = 0;
    this->periodS1 = this->getPeriod() * this->S1;
    this->periodS2 = this->getPeriod() * this->S2;

}
  
void SweepTask::init(int period){
    Task::init(period); 
    this->servo = new ServoMotor(pinServo, sectors);
    this->pot = new Potentiometer(pinPot);
}

void SweepTask::tick(){
    Context& context = Context::getInstance();
    if (context.isRSU()){
        if (context.isWorking()) {
            this->setPeriod(this->periodS1);
            currentSector = servo->sweep();
            context.setCurrentSector(currentSector);
        } else if (context.isPreAlarm()) {
            this->setPeriod(this->periodS2);
            servo->sweep();
        } else if (context.isAlarm()) {
            int angle = map(pot->getValue(), 0, 1023, 0, 180);
            servo->setPosition(angle);
        }else if (context.isIdle()) {
            servo->setPosition(0);
        }
    } else if (context.isRight()) {
        context.setWaiting();
        servo->setDirection(1);
        currentSector = servo->sweep();
        context.setCurrentSector(currentSector);
    } else if (context.isLeft()) {
        context.setWaiting();
        servo->setDirection(-1);
        currentSector = servo->sweep();
        context.setCurrentSector(currentSector);
    } 
}
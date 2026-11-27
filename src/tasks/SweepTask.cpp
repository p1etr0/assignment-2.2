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
    switch (context.getControlSweep())
    {
    case RSU:
        switch (context.getState())
        {
        case IDLE: 
            servo->setPosition(0);
            break;
        case WORKING:
            this->setPeriod(this->periodS1);
            currentSector = servo->sweep();
            context.setCurrentSector(currentSector);
            break;
        case PRE_ALARM:
            this->setPeriod(this->periodS2);
            servo->sweep();
            break;
        case ALARM:
            angle = map(pot->getValue(), 0, 1023, 0, 180);
            servo->setPosition(angle);
            break;
        default:
            break;
        }
        break;
    case RIGHT:
        context.setWaiting();
        servo->setDirection(1);
        currentSector = servo->sweep();
        context.setCurrentSector(currentSector);
    case LEFT:
        context.setWaiting();
        servo->setDirection(-1);
        currentSector = servo->sweep();
        context.setCurrentSector(currentSector);
    default:
        break;
    }
}
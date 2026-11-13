#include "AutoSweepTask.h"
#include "Arduino.h"

AutoSweepTask::AutoSweepTask(int pinServo){
    this->pinServo = pinServo;
}
  
void AutoSweepTask::init(int period){
    Task::init(period); 
    this->servo = new ServoMotor(pinServo, 10);
}

void AutoSweepTask::tick(){
    servo->sweep();
}
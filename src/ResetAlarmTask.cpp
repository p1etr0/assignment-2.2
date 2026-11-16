#include "ResetAlarmTask.h"
#include "Arduino.h"

ResetAlarmTask::ResetAlarmTask(int pinLed, int pinServo){
  this->pinLed = pinLed;
  this->pinServo = pinServo;
}
  
void ResetAlarmTask::init(int period){
  Task::init(period); 
  this->servo = new ServoMotor(pinServo, 10);
  this->led = new Led(pinLed);
}
  
void ResetAlarmTask::tick(){
    led->switchOff();
    servo->setPosition(0);
}
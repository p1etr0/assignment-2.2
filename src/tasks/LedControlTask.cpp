#include "LedControlTask.h"
#include "Context.h"

LedControlTask::LedControlTask(int pinRed, int pinGreen){
  this->pinRed = pinRed;
  this->pinGreen = pinGreen;
}
  
void LedControlTask::init(int period){
  Task::init(period);
  redLed = new Led(pinRed);
  greenLed = new Led(pinGreen); 
  redState = OFF;  
  greenState = OFF;   
}
  
void LedControlTask::tick(){
  switch (Context::getInstance().getState())
  {
  case IDLE:
    greenState = OFF;
    greenLed->switchOff();
    break;
  case WORKING:
    greenState = ON;
    greenLed->switchOn();
    redState = OFF;
    redLed->switchOff();
    break;
  case PRE_ALARM:
    greenState = OFF;
    greenLed->switchOff();
    redState = ON;
    redLed->switchOn();
    break;
  case ALARM:
    switch (redState){
      case OFF:
        redLed->switchOn();
        redState = ON; 
        break;
      case ON:
        redLed->switchOff();
        redState = OFF;
        break;
    }
    break;
  default:
    break;
  }
}
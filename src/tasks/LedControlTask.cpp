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
    if (Context::getInstance().isIdle()) {
        greenState = OFF;
        greenLed->switchOff();
    } else if (Context::getInstance().isWorking()) {
        greenState = ON;
        greenLed->switchOn();
        redState = OFF;
        redLed->switchOff();
    } else if (Context::getInstance().isPreAlarm()) {
        greenState = OFF;
        greenLed->switchOff();
        redState = ON;
        redLed->switchOn();
    } else if (Context::getInstance().isAlarm()) {
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
    }
}
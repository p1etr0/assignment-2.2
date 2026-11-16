#include "SwitchOffTask.h"
#include "Arduino.h"

SwitchOffTask::SwitchOffTask(int pin){
  this->pin = pin;    
}
  
void SwitchOffTask::init(){
  Task::init();
  led = new Led(pin); 
  state = ON;    
}
  
void SwitchOffTask::tick(){
    led->switchOff();
    state = OFF;
}
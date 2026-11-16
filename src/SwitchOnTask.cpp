#include "SwitchOnTask.h"
#include "Arduino.h"

SwitchOnTask::SwitchOnTask(int pin){
  this->pin = pin;    
}
  
void SwitchOnTask::init(){
  Task::init();
  led = new Led(pin); 
  state = OFF;    
}
  
void SwitchOnTask::tick(){
    led->switchOn();
    state = ON;
}
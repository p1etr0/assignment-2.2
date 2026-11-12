#include "SwitchOnTask.h"
#include "Arduino.h"

SwitchOnTask::SwitchOnTask(int pin){
  this->pin = pin;    
}
  
void SwitchOnTask::init(int period){
  Task::init(period);
  led = new Led(pin); 
  state = OFF;    
}
  
void SwitchOnTask::tick(){
    led->switchOn();
    state = ON;
}
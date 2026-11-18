#include "BlinkingTask.h"
#include "Arduino.h"

BlinkingTask::BlinkingTask(int pin){
  this->pin = pin;
}

void BlinkingTask::init(int period){
  Task::init(period);
  led = new Led(pin); 
  ledState = OFF;
}

void BlinkingTask::tick(){
  switch (ledState){
    case OFF:
      led->switchOn();
      ledState = ON; 
      break;
    case ON:
      led->switchOff();
      ledState = OFF;
      break;
  }
}
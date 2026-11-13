#include "ManualSweepTask.h"
#include "Arduino.h"

ManualSweepTask::ManualSweepTask(int pinServo, int pinPot){
  this->pinServo = pinServo;
  this->pinPot = pinPot;
}
  
void ManualSweepTask::init(int period, int sectors){
  Task::init(period);
  servo = new ServoMotor(pinServo, sectors);    
  pot = new Potentiometer(pinPot);  
}
  
void ManualSweepTask::tick(){
    int angle = map(pot->getValue(), 0, 1023, 0, 180);
    servo->setPosition(angle);
    Serial.print("Potentiometer value: " + String(pot->getValue()) + " | Servo angle: " + String(angle) + "\n");
}

#include "Scheduler.h"
#include "Arduino.h"

void Scheduler::init(int basePeriod){
  this->basePeriod = basePeriod;
  // timer.setupPeriod(basePeriod);  
  nTasks = 0;
  this->sonarState = IDLE;
}

void Scheduler::changeState(float distance){
  sonarState = WORKING;
  if (distance > D1 && distance < D2){
    sonarState = ALARM;
  } else {
    sonarState = PRE_ALARM;
  }
}


RadarState Scheduler::getState(){
  return sonarState;
}

bool Scheduler::addTask(Task* task){
  if (nTasks < MAX_TASKS-1){
    taskList[nTasks] = task;
    nTasks++;
    return true;
  } else {
    return false; 
  }
}
  
void Scheduler::schedule(){ 
  for (int i = 0; i < nTasks; i++){
    if (taskList[i]->isActive()){
      if (taskList[i]->isPeriodic()){
        if (taskList[i]->updateAndCheckTime(basePeriod)){
          taskList[i]->tick();
        }
      } else {
        taskList[i]->tick();
        if (taskList[i]->isCompleted()){
          taskList[i]->setActive(false);
        }
      }
    }
  }
  nTasks = 0;
}
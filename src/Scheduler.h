#ifndef __SCHEDULER__
#define __SCHEDULER__

#include "Task.h"
#include "Types.h"

#define MAX_TASKS 10

class Scheduler {

  int basePeriod;
  int nTasks;
  RadarState sonarState;
  Task* taskList[MAX_TASKS]; 
  const int D1 = 1;
  const int D2 = 2; 
  // Timer timer;

public:
  void init(int basePeriod);  
  void changeState(float distance);
  RadarState getState();
  virtual bool addTask(Task* task);  
  virtual void schedule();
};

#endif
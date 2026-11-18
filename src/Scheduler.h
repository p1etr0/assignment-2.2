#ifndef __SCHEDULER__
#define __SCHEDULER__

#include "Task.h"
#include "Context.h"

#define MAX_TASKS 10

class Scheduler {

  int basePeriod;
  int nTasks;
  Task* taskList[MAX_TASKS]; 
  const int D1 = 1;
  const int D2 = 2; 

public:
  void init(int basePeriod);  
  virtual bool addTask(Task* task);  
  virtual void schedule();
};

#endif
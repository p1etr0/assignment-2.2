#include "Arduino.h"

#include "Context.h"

#include "Scheduler.h"

#include "tasks/SleepTask.h"
#include "tasks/SweepTask.h"
#include "tasks/LedControlTask.h"
#include "tasks/SenseDistanceTask.h"

#define POT A0
#define TEMP A1
#define START_STOP 2
#define RESET 3
#define GREEN_LED 5
#define RED_LED 6
#define ECHO 7
#define TRIG 8
#define MOTOR 9


Context& context = Context::getInstance();

const int sectors = 5;
bool sleepFlag = false;

Scheduler* scheduler;

SleepTask* sleepTask;
LedControlTask* ledControlTask;
SweepTask* sweepTask;
SenseDistanceTask* senseDistanceTask;



void resetAction() {
    if (context.isAlarm()){
        context.setWorking();
    }
}

void startStopActions() {
    if (context.isIdle()) {
        context.setWorking();
    } else if (context.isWorking()) {
        context.setIdle();
        sleepFlag = true;
        
        //scheduler->schedule();
        
    }
}

void setup() {
    pinMode(TEMP, INPUT);
    pinMode(START_STOP, INPUT);
    pinMode(RESET, INPUT);
    pinMode(GREEN_LED, OUTPUT);
    pinMode(RED_LED, OUTPUT);
    pinMode(TRIG, OUTPUT);
    pinMode(ECHO, INPUT);
    pinMode(POT, INPUT);

    attachInterrupt(digitalPinToInterrupt(RESET), resetAction, RISING);
    attachInterrupt(digitalPinToInterrupt(START_STOP), startStopActions, RISING);

    Serial.begin(115200);
    
    scheduler = new Scheduler();
    scheduler->init(100);

    sleepTask = new SleepTask();
    sleepTask->init();

    sweepTask = new SweepTask(MOTOR, POT, sectors);
    sweepTask->init(100);

    ledControlTask = new LedControlTask(RED_LED, GREEN_LED);
    ledControlTask->init(100);

    senseDistanceTask = new SenseDistanceTask(TRIG, ECHO, TEMP, sectors);
    senseDistanceTask->init(100);

    sleepTask->setActive(true);

    
    scheduler->addTask(ledControlTask);
    scheduler->addTask(sweepTask);
    scheduler->addTask(senseDistanceTask);
    scheduler->addTask(sleepTask);
   

}

void loop() {
    Serial.println("sct:" + String(sectors));
    if (sleepFlag) {
        sleepFlag = false;
        sleepTask->setActive(true);
    }
    scheduler->schedule();

}


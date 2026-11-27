#include "Arduino.h"

#include "Context.h"

#include "Scheduler.h"

#include "components/MsgService.h"

#include "tasks/SleepTask.h"
#include "tasks/SweepTask.h"
#include "tasks/LedControlTask.h"
#include "tasks/SenseDistanceTask.h"
#include "tasks/ReadMsgTask.h"

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

Scheduler* scheduler;

SleepTask* sleepTask;
LedControlTask* ledControlTask;
SweepTask* sweepTask;
SenseDistanceTask* senseDistanceTask;
ReadMsgTask* readMsgTask;



void resetAction() {
    if (context.getState() == ALARM){
        context.setWorking();
    }
}

void startStopActions() {
    switch (context.getState())
    {
    case IDLE:
        context.setWorking();
        break;
    case WORKING:
        context.setIdle();   
        break;
    default:
        break;
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

    readMsgTask = new ReadMsgTask();
    readMsgTask->init(100);
    sleepTask->setActive(true);

    
    scheduler->addTask(ledControlTask);
    scheduler->addTask(sweepTask);
    scheduler->addTask(senseDistanceTask);
    scheduler->addTask(readMsgTask);
    scheduler->addTask(sleepTask);

}

void loop() {
    Serial.println("sct:" + String(sectors));
    if (context.getSleepFlag()) {
        context.setSleepFlag(false);
        sleepTask->setActive(true);
    }
    scheduler->schedule();
    context.getState() == IDLE ?  Serial.println("st:IDLE") :
    context.getState() == WORKING ? Serial.println("st:WORKING") :
    context.getState() == PRE_ALARM ? Serial.println("st:PRE_ALARM")  :
    context.getState() == ALARM ? Serial.println("st:ALARM")  : 
    Serial.println("");
    //Context::getInstance().isIdle() ? Serial.println("st:IDLE") :Context::getInstance().isWorking() ? Serial.println("st:WORKING") : Context::getInstance().isPreAlarm() ? Serial.println("st:PREALARM") : Context::getInstance().isAlarm() ? Serial.println("st:ALARM"):Serial.println("");
}


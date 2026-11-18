#include <Arduino.h>

#include "Context.h"

#include "Scheduler.h"

#include "SweepTask.h"
#include "LedControlTask.h"
#include "SenseDistanceTask.h"

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

Scheduler* scheduler;

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

    Serial.begin(9600);

    scheduler = new Scheduler();
    scheduler->init(100);


    sweepTask = new SweepTask(MOTOR, POT);
    sweepTask->init(1000);

    ledControlTask = new LedControlTask(RED_LED, GREEN_LED);
    ledControlTask->init(30000);

    senseDistanceTask = new SenseDistanceTask(TRIG, ECHO, TEMP);
    senseDistanceTask->init(100);

    scheduler->addTask(ledControlTask);
    scheduler->addTask(sweepTask);
    scheduler->addTask(senseDistanceTask);
}

void loop() {
    scheduler->schedule();
}


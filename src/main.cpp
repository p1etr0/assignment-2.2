#include <Arduino.h>
#include <LiquidCrystal_I2C.h>

#include "Led.h"
#include "BlinkingTask.h"
#include "ResetAlarmTask.h"
#include "SweepTask.h"

#include "LedControlTask.h"
#include "SenseDistanceTask.h"
#include "Scheduler.h"

#include "Context.h"

#define TEMP A1
#define START_STOP 2
#define RESET 3
#define GREEN_LED 5
#define RED_LED 6
#define ECHO 7
#define TRIG 8
#define POT A0
#define MOTOR 9

Scheduler* scheduler;
LedControlTask* ledControlTask;
SweepTask* sweepTask;

BlinkingTask* blinkingTask;

ResetAlarmTask* resetAlarmTask;
SenseDistanceTask* senseDistanceTask;

Context& context = Context::getInstance();

// inizializzazione dei led
Led* greenLed;
Led* redLed;

void resetAction() {
    if (context.isAlarm()){
        //scheduler->addTask(resetAlarmTask);
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

    Serial.begin(9600);


    scheduler = new Scheduler();
    scheduler->init(100);

    //blinkingTask = new BlinkingTask(RED_LED);
    //-blinkingTask->init(30000);
    

    sweepTask = new SweepTask(MOTOR, POT);
    sweepTask->init(1000);


    //resetAlarmTask = new ResetAlarmTask(RED_LED, MOTOR);
    //resetAlarmTask->init(100);
    attachInterrupt(digitalPinToInterrupt(RESET), resetAction, RISING);
    attachInterrupt(digitalPinToInterrupt(START_STOP), startStopActions, RISING);

    //switchOnGreenTask = new SwitchOnTask(GREEN_LED);
    //switchOnGreenTask->init();
    //switchOffGreenTask = new SwitchOffTask(GREEN_LED);
    //switchOffGreenTask->init();
//
    //switchOnRedTask = new SwitchOnTask(RED_LED);
    //switchOnRedTask->init();
    //switchOffRedTask = new SwitchOffTask(RED_LED);
    //switchOffRedTask->init();
    //
    ledControlTask = new LedControlTask(RED_LED, GREEN_LED);
    ledControlTask->init(30000);
    senseDistanceTask = new SenseDistanceTask(TRIG, ECHO, TEMP);
    senseDistanceTask->init(100);
//
    //greenLed = new Led(GREEN_LED);
    //redLed = new Led(RED_LED);
    scheduler->addTask(ledControlTask);
    scheduler->addTask(sweepTask);
    scheduler->addTask(senseDistanceTask);
    //scheduler->addTask();
}

void loop() {
    scheduler->schedule();
}


#include <Arduino.h>
#include <LiquidCrystal_I2C.h>

#include "Led.h"
#include "BlinkingTask.h"
#include "ManualSweepTask.h"
#include "ResetAlarmTask.h"
#include "AutoSweepTask.h"
#include "SwitchOnTask.h"
#include "SwitchOffTask.h"
#include "SenseDistanceTask.h"
#include "Scheduler.h"
#include "Types.h"

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
BlinkingTask* blinkingTask;
ManualSweepTask* manualSweepTask;
ResetAlarmTask* resetAlarmTask;

AutoSweepTask* autoSweepTask;

SwitchOnTask* switchOnGreenTask;
SwitchOffTask* switchOffGreenTask;
SwitchOffTask* switchOffRedTask;
SwitchOnTask* switchOnRedTask;

SenseDistanceTask* senseDistanceTask;

void resetAction() {
    if (radarState == ALARM){
        scheduler->addTask(resetAlarmTask);
        radarState = WORKING;
    }
}

void startStopActions() {
    radarState = radarState == IDLE ? WORKING : radarState == WORKING ? IDLE : radarState;
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

    blinkingTask = new BlinkingTask(RED_LED);
    blinkingTask->init(30000);
    

    manualSweepTask = new ManualSweepTask(MOTOR, POT);
    manualSweepTask->init(100, 10);
    resetAlarmTask = new ResetAlarmTask(RED_LED, MOTOR);
    resetAlarmTask->init(100);
    attachInterrupt(digitalPinToInterrupt(RESET), resetAction, RISING);
    attachInterrupt(digitalPinToInterrupt(START_STOP), startStopActions, RISING);

    switchOnGreenTask = new SwitchOnTask(GREEN_LED);
    switchOnGreenTask->init();
    switchOffGreenTask = new SwitchOffTask(GREEN_LED);
    switchOffGreenTask->init();

    switchOnRedTask = new SwitchOnTask(RED_LED);
    switchOnRedTask->init();
    switchOffRedTask = new SwitchOffTask(RED_LED);
    switchOffRedTask->init();
    
    senseDistanceTask = new SenseDistanceTask(TRIG, ECHO, TEMP);
    senseDistanceTask->init(100);
    autoSweepTask = new AutoSweepTask(MOTOR);
    autoSweepTask->init(1000);

}

void loop() {
    switch (radarState)
    {
    case IDLE:
        scheduler->addTask(switchOffGreenTask);
        scheduler->addTask(switchOffRedTask);
        break;

    case WORKING:
        scheduler->addTask(autoSweepTask);
        scheduler->addTask(switchOnGreenTask);
        scheduler->addTask(senseDistanceTask);
        break;

    case PRE_ALARM:
        scheduler->addTask(switchOffGreenTask);
        scheduler->addTask(autoSweepTask);
        scheduler->addTask(switchOnRedTask);
        scheduler->addTask(senseDistanceTask);
        break;

    case ALARM:
        scheduler->addTask(blinkingTask);
        scheduler->addTask(manualSweepTask);
        break;
    
    default:
        break;
    }
    Serial.println(radarState);
    scheduler->schedule();
}


#include <Arduino.h>
#include <LiquidCrystal_I2C.h>

#include "Led.h"
#include "BlinkingTask.h"
#include "ManualSweepTask.h"
#include "ResetAlarmTask.h"
#include "AutoSweepTask.h"
#include "SwitchOnTask.h"
#include "SenseDistanceTask.h"
#include "Scheduler.h"
#include "Types.h"

#define TEMP A1
#define START_STOP 4
#define RESET 3
#define GREEN_LED 5
#define RED_LED 6
#define ECHO 7
#define TRIG 8
#define POT A0
#define MOTOR 9

RadarState radarState = ALARM;
Scheduler* scheduler;
BlinkingTask* blinkingTask;
ManualSweepTask* manualSweepTask;
ResetAlarmTask* resetAlarmTask;

AutoSweepTask* autoSweepTask;
SwitchOnTask* switchOnTask;
SenseDistanceTask* senseDistanceTask;

void swapToWorking() {
    if (radarState == ALARM){
        scheduler->addTask(resetAlarmTask);
        radarState = WORKING;
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

    blinkingTask = new BlinkingTask(RED_LED);
    blinkingTask->init(30000);
    

    manualSweepTask = new ManualSweepTask(MOTOR, POT);
    manualSweepTask->init(100, 10);
    resetAlarmTask = new ResetAlarmTask(RED_LED, MOTOR);
    resetAlarmTask->init(100);
    attachInterrupt(digitalPinToInterrupt(RESET), swapToWorking, RISING);

    switchOnTask = new SwitchOnTask(GREEN_LED);
    switchOnTask->init();
    senseDistanceTask = new SenseDistanceTask(TRIG, ECHO, TEMP);
    senseDistanceTask->init(100);
    autoSweepTask = new AutoSweepTask(MOTOR);
    autoSweepTask->init(100);
}

void loop() {
    switch (radarState)
    {
    case IDLE:
        /* code */
        break;

    case WORKING:
        scheduler->addTask(autoSweepTask);
        scheduler->addTask(switchOnTask);
        scheduler->addTask(senseDistanceTask);
        radarState = scheduler->getState();
        break;

    case PRE_ALARM:
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


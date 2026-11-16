#include <Arduino.h>
#include <LiquidCrystal_I2C.h>

#include "Led.h"
#include "BlinkingTask.h"
#include "ManualSweepTask.h"
#include "ResetAlarmTask.h"
#include "AutoSweepTask.h"
#include "SwitchOnTask.h"
#include "SenseD1Task.h"
#include "Scheduler.h"
#include "Types.h"

#define TEMP A1
#define START_STOP 4
#define RESET 3
#define GREEN_LED 5
#define RED_LED 6
#define ECHO 8
#define TRIG 7
#define POT A0
#define MOTOR 9

RadarState radarState = ALARM;
Scheduler* scheduler;
BlinkingTask* blinkingTask;
ManualSweepTask* manualSweepTask;
ResetAlarmTask* resetAlarmTask;

AutoSweepTask* autoSweepTask;
SwitchOnTask* switchOnTask;
SenseD1Task* senseD1Task;

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
    senseD1Task = new SenseD1Task(ECHO, TRIG, TEMP);
    senseD1Task->init(100);
}

void loop() {
    switch (radarState)
    {
    case IDLE:
        /* code */
        break;

    case WORKING:
        //scheduler->addTask(autoSweepTask);
        scheduler->addTask(switchOnTask);
        scheduler->addTask(senseD1Task);
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

    scheduler->schedule();
}


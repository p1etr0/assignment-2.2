#include <Arduino.h>
#include <LiquidCrystal_I2C.h>
#include <Servo.h>

#include "Led.h"
#include "BlinkingTask.h"
#include "ManualSweepTask.h"
#include "Scheduler.h"
#include "Types.h"

#define TEMP A1
#define START_STOP 3
#define RESET 4
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
    blinkingTask->init(100);
    

    manualSweepTask = new ManualSweepTask(MOTOR, POT);
    manualSweepTask->init(100, 10);
    
    scheduler->addTask(blinkingTask);
    scheduler->addTask(manualSweepTask);
}

void loop() {
    switch (radarState)
    {
    case IDLE:
        /* code */
        break;

    case WORKING:
        
        break;

    case PRE_ALARM:
        /* code */
        break;

    case ALARM:
        
        break;
    
    default:
        break;
    }

    scheduler->schedule();
}


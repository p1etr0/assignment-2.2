#include "SleepTask.h"
#include "Context.h"
#include <avr/sleep.h>
#include <Arduino.h>

SleepTask::SleepTask(){
}

void SleepTask::init(){ 
}
  
void SleepTask::tick(){
    if (Context::getInstance().getState() == IDLE) {
        set_sleep_mode(SLEEP_MODE_PWR_DOWN);
        noInterrupts(); // Disable interrupts to ensure the sleep mode is set before enabling sleep
        sleep_enable();
        interrupts(); // Re-enable interrupts so the MCU can wake up
        sleep_cpu();
        sleep_disable();
        Context::getInstance().setWorking();
    }
}
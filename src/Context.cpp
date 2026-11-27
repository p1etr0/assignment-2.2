#include "Context.h"

// Il costruttore ora è privato e viene richiamato solo internamente da getInstance()
Context::Context() {
    this->radarState = IDLE;
    this->currentSector = 0;
    this->controlSweep = RSU;
    this->sleepFlag = true;
}

RadarState Context::getState() {
    return radarState;
}

int Context::getCurrentSector() {
    return this->currentSector;
}

ControlSweep Context::getControlSweep(){
    return this->controlSweep;
}

bool Context::getSleepFlag(){
    return this->sleepFlag;
}

void Context::setIdle() {
    this->setRSU();
    this->setSleepFlag(true);
    this->radarState = IDLE;
}

void Context::setWorking() {
    this->radarState = WORKING;
}

void Context::setPreAlarm() {
    this->radarState = PRE_ALARM;
}

void Context::setAlarm() {
    this->radarState = ALARM;
}

void Context::setCurrentSector(int currentSector) {
    this->currentSector = currentSector;
}

void Context::setRSU(){
    this->controlSweep = RSU;
}

void Context::setWaiting(){
    this->controlSweep = WAITING;
}

void Context::setRight(){
    this->controlSweep = RIGHT;
}

void Context::setLeft(){
    this->controlSweep = LEFT;
}

void Context::setSleepFlag(bool flag){
    this->sleepFlag = flag;
}
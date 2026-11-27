#include "Context.h"

// Il costruttore ora è privato e viene richiamato solo internamente da getInstance()
Context::Context() {
    this->radarState = IDLE;
    this->currentSector = 0;
    this->controlSweep = RSU;
    this->sleepFlag = true;
}

bool Context::isIdle() {
    return radarState == IDLE;
}

bool Context::isWorking() {
    return radarState == WORKING;
}

bool Context::isPreAlarm() {
    return radarState == PRE_ALARM;
}

bool Context::isAlarm() {
    return radarState == ALARM;
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

int Context::getCurrentSector() {
    return currentSector;
}

bool Context::isRSU(){
    return this->controlSweep == RSU;
}

bool Context::isWaiting(){
    return this->controlSweep == WAITING;
}

bool Context::isRight(){
    return this->controlSweep == RIGHT;
}

bool Context::isLeft(){
    return this->controlSweep == LEFT;
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

bool Context::getSleepFlag(){
    return this->sleepFlag;
}

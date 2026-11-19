#include "Context.h"

// Il costruttore ora è privato e viene richiamato solo internamente da getInstance()
Context::Context() {
    this->radarState = IDLE;
    this->currentSector = 0;
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
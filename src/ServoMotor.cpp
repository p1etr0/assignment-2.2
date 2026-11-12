#include "ServoMotor.h"
#include "Arduino.h"

ServoMotor::ServoMotor(int pin, int sectors) {
    this->pin = pin;
    this->sectors = sectors;
}

void ServoMotor::on() {
    this->isOn = true;
    // il tick fa avanzare o tornare indietro di un valore degli n
    // in base allo stato del servomotore (da creare)

    // posAttuale += (direzione{-1, 1} * settore)
}

bool ServoMotor::getState() {
    return this->isOn;
}




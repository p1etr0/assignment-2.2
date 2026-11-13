#include "ServoMotor.h"
#include "Arduino.h"

ServoMotor::ServoMotor(int pin, int sectors) {
    this->pin = pin;
    this->sectors = sectors;
    this->dir = FORWARD;
    this->position = 0;
}

void ServoMotor::sweep() {
    // il tick fa avanzare o tornare indietro di un valore degli n
    // in base alla direzione del servomotore
    position += (dir * sectors);

    if(position >= 180) {
        dir = BACKWARD;
    } else if(position <= 0) {
        dir = FORWARD;
    }
}

void ServoMotor::setPosition(int angle) {
    this->position = angle;
    // richiamare la libreria Timer2
}






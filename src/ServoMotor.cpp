#include "ServoMotor.h"
#include "Arduino.h"



ServoMotor::ServoMotor(int pin, int sectors) {
    this->pin = pin;
    this->sectors = sectors;
    this->dir = FORWARD;
    this->position = 0;
    this->motor.attach(pin);
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

    setPosition(position);
}

void ServoMotor::setPosition(int angle) {
    this->position = angle;

    // valori personalizzati per il nostro servo motore
    float coeff = (2400.0-544.0)/180;
    motor.write(544 + angle*coeff);
    // TO DO: DA TESTARE
}






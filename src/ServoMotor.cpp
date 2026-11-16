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
    angle = constrain(angle, 0, 180);
    this->position = angle;

    float coeff = (2400.0 - 544.0) / 180.0;
    int pulse = 544 + angle * coeff;
    Serial.print(pulse);
    motor.write(pulse);
}






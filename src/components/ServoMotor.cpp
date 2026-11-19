#include "ServoMotor.h"
#include "Arduino.h"



ServoMotor::ServoMotor(int pin, int sectors) {
    this->pin = pin;
    this->sectorSpan = ((int)(180 / (sectors-1)));
    this->dir = FORWARD;
    this->position = 0;
    this->motor.attach(pin);
    this->currentSector = 0;
}

int ServoMotor::sweep() {
    // il tick fa avanzare o tornare indietro di un valore degli n
    // in base alla direzione del servomotore
    
    if(position >= 180) {
        dir = BACKWARD;
    } else if(position <= 0) {
        dir = FORWARD;
    }

    position += dir * sectorSpan;

    setPosition(position);
    currentSector = position / sectorSpan;
    Serial.print("Current position: ");
    Serial.println(position);
    Serial.print("Current sector: ");   
    Serial.println(currentSector);
    return currentSector;
}

void ServoMotor::setPosition(int angle) {
    angle = constrain(angle, 0, 180);
    this->position = angle;     
    int pulse = map(angle, 0, 180, 544, 2400);
    motor.write(pulse);
}






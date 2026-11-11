#include <Arduino.h>
#include <LiquidCrystal_I2C.h>
#include <Servo.h>

#define TEMP A1
#define START_STOP 3
#define RESET 4
// #define GREEN_LED 5
// #define RED_LED 6
#define ECHO 7
#define TRIG 8
#define POT A0
#define MOTOR 9



Servo myservo;  // create servo object to control a servo

int val;    // variable to read the value from the analog pin

const float vs = 331.5 + 0.6*19.2;

void setup() {
    pinMode(TEMP, INPUT);
    pinMode(START_STOP, INPUT);
    pinMode(RESET, INPUT);
    // pinMode(GREEN_LED, OUTPUT);
    // pinMode(RED_LED, OUTPUT);
    pinMode(TRIG, OUTPUT);
    pinMode(ECHO, INPUT);
    pinMode(POT, INPUT);

    Serial.begin(9600);

    myservo.attach(9);
}

void loop() {
    val = analogRead(POT);   
    val = map(val, 0, 1023, 0, 180);     // scale it to use it with the servo (value between 0 and 180)
    myservo.write(val);// sets the servo position according to the scaled value
    Serial.println(val);
    delay(15);  
}


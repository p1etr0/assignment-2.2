#include "Lcd.h"
#include "Context.h"

Lcd::Lcd() {
    this->lcd = new LiquidCrystal_I2C(0x27, 16, 2);
    lcd->init();
}

void Lcd::write(int currentSector, bool objectDetected) {
    lcd->setCursor(0, 0);
    lcd->print("Sector: " + currentSector);
    lcd->setCursor(0, 1);
    lcd->print("Obj detected: " + objectDetected ? "Yes" : "No");
}

void Lcd::clear() {
    lcd->noBacklight();
    lcd->noDisplay();
}
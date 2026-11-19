#include "Lcd.h"
#include "Context.h"

Lcd::Lcd() {
    this->lcd = new LiquidCrystal_I2C(0x27, 16, 2);
    lcd->init();
}

void Lcd::write(int currentSector, bool objectDetected) {
    lcd->clear();
    lcd->backlight();
    lcd->display(); 
    lcd->setCursor(0, 0);
    lcd->print("Sector: " + String(currentSector));
    lcd->setCursor(0, 1);
    lcd->print("Object: " + String(objectDetected ? "Yes" : "No"));
}

void Lcd::clear() {
    lcd->noBacklight();
    lcd->noDisplay();
}
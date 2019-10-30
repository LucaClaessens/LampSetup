#include "TM1637Display.h"
#include "LampSetup.h"
#include "Arduino.h"

LampSetup::LampSetup(uint8_t relayPin, uint8_t buttonPin, uint8_t CLK, uint8_t DIO): 
    ledDisplay(TM1637Display(CLK, DIO)),
    relayPin(relayPin),
    buttonPin(buttonPin)
{
}

bool LampSetup::relayDebouncePassed(){
    return this->now > this->relayToLow;
}

void LampSetup::setRelayLow(){
    digitalWrite(this->relayPin, LOW);
    this->relayState = 0;
}

void LampSetup::setRelayHigh(){
    digitalWrite(this->relayPin, HIGH);
    this->relayToLow = this->now + this->debounceTime;
    this->relayState = 1;
}

void LampSetup::buttonStateChanged(int buttonState){
        if (buttonState == HIGH && (!this->buttonHadFirstClick || this->relayDebouncePassed())) {
        this->buttonClicked();
    }
}

void LampSetup::incrementCounter(){
    this->counter += 1;
    this->ledDisplay.showNumberDec(this->counter, true);
}

void LampSetup::buttonClicked(){

    if(!this->buttonHadFirstClick){
    this->buttonHadFirstClick = true;
    }
    
    this->setRelayHigh();
    this->incrementCounter();
}

void LampSetup::setup(){

    this->now = millis();
    this->nextValidClick = this->now;
    this->nextBlockRelease = 0;
    this->relayToLow = 0;
    this->relayState = 0;
    this->buttonState = 0;
    this->buttonStateLastTick = 0;
    this->buttonHadFirstClick = false;
    this->counter = 0;
    this->debounceTime = 3000;

    pinMode(this->relayPin, OUTPUT);
    pinMode(this->buttonPin, OUTPUT);
    digitalWrite(this->buttonPin, HIGH);
    digitalWrite(this->relayPin, HIGH);

    this->ledDisplay.setBrightness(0x0f);
    this->ledDisplay.showNumberDec(0, true);
}

void LampSetup::update(){
    this->now = millis();

    if(this->relayDebouncePassed()){
    this->setRelayLow();
    }

    this->buttonState = digitalRead(this->buttonPin);

    if(this->buttonState != this->buttonStateLastTick){
        this->buttonStateChanged(this->buttonState);
    }

    this->buttonStateLastTick = this->buttonState;
}
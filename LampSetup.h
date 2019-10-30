/*
  LampSetup
  Created by Luca Claessens
*/
#ifndef _LampSetup_
#define _LampSetup_

#include "Arduino.h"
#include "TM1637Display.h"

class LampSetup {
public:
    LampSetup(uint8_t relayPin, uint8_t buttonPin, uint8_t CLK, uint8_t DIO);
    void setup();
    void update();
private:
    bool buttonHadFirstClick;
    int counter;
    int relayState;
    int buttonState;
    int buttonStateLastTick;
    unsigned long now;
    unsigned long nextValidClick;
    unsigned long nextBlockRelease;
    unsigned long relayToLow;
    unsigned long debounceTime;
    int relayPin;
    int buttonPin;
    TM1637Display ledDisplay;
    boolean relayDebouncePassed();
    void setRelayLow();
    void setRelayHigh();
    void buttonStateChanged(int buttonState);
    void buttonClicked();
    void incrementCounter();
};
#endif
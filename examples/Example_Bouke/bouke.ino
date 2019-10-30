#include <LampSetup.h>

#define DIO_GREEN 3
#define CLK_GREEN 2
#define BTN_GREEN 9
#define RELAY_GREEN 7

#define DIO_RED 5
#define CLK_RED 4
#define BTN_RED 10
#define RELAY_RED 8

LampSetup setupGreen(RELAY_GREEN, BTN_GREEN, CLK_GREEN, DIO_GREEN);
LampSetup setupRed(RELAY_RED, BTN_RED, CLK_RED, DIO_RED);

void setup() {
  setupGreen.setup();
  setupRed.setup();
}

void loop(){
  setupGreen.update();
  setupRed.update();
}

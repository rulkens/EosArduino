
/*************************************************** 

The main Arduino controller with FastLed support

- uses the 12 pixel NeoPixel circle
- the CAP1188 I2C/SPI 8-chan Capacitive Sensor

Written by Alexander Rulkens
 ****************************************************/
#include <FastLED.h>
#include <Wire.h>
#include <SPI.h>
#include <Adafruit_CAP1188.h>

#define NUM_LEDS    12

/* STATES */
#define STATE_SETUP      0 // "setup"
#define STATE_STARTUP    1 // "startup"
#define STATE_OK         2 // "ok"
#define STATE_ERROR      3 // "error"
#define STATE_PROG_RUN   4 // "progRun" - running a program

#define STATE_TOUCH      10 // "touch"
#define STATE_TOUCH_LONG 11 // "longtouch"
#define STATE_TOUCH_XLONG 12 // "xlongtouch"

/* GLOBALS */
CRGB leds[NUM_LEDS];

// OK color
CRGB c_ok = CRGB(0,255,0);

int state;
boolean stateHasChanged = false;
int breatheTimeout = 0;

void setup() {
  
  delay(300);
  
  initSerial();
  
  setState(STATE_SETUP);
  initLeds();
  
  delay(1000); // sanity delay
  
  log("setup");
  
  initTouch();
  initLeds();
  
  // go to default state
  setState(STATE_STARTUP);
}

void loop(){
  // Add entropy to random number generator; we use a lot of it.
  random16_add_entropy(random());
  
  loopTouch();
  loopSerial();
  
  // TODO: do some state machine magic here
  loopLeds();
  loopState();
}


/*************************************************** 

 The main Arduino controller with FastLED support

 - uses the 12 pixel NeoPixel circle
 - the CAP1188 I2C/SPI 8-chan Capacitive Sensor

 Written by Alexander Rulkens
 ****************************************************/
#include <FastLED.h>
#include <Wire.h>
#include <SPI.h>
#include <Adafruit_CAP1188.h>
#include "touch.h"
#include "state.h"
#include "leds.h"

#define NUM_LEDS    12

/* GLOBALS */
CRGB leds[NUM_LEDS];

// OK color
CRGB c_ok = CRGB(0,255,0);

/** 
the main application state
*/
int state;
boolean touchStateHasChanged = false;
/**
the main touch state. can be one of the touch states
*/
int touch_state;
boolean stateHasChanged = false;


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
  
  // INPUT
  loopTouch();
  loopSerial();
  
  // OUTPUT
  loopLeds();
  loopState();
  
  // cleaning up
  endLoopState();
  endLoopTouch();
}

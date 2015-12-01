/* LED SETTINGS */
#define LED_PIN       4
//#define CLOCK_PIN   5
#define DATA_PIN      6
//#define COLOR_ORDER GRB
#define CHIPSET     NEOPIXEL
#define NUM_LEDS    12

// blends the ok color 
#define COLOR_OK_BLEND_SPEED 10

#define FRAMES_PER_SECOND 100

void initLeds() {
  FastLED.addLeds<CHIPSET, DATA_PIN>(leds, NUM_LEDS).setCorrection( TypicalLEDStrip );
  FastLED.setBrightness( BRIGHTNESS );
  
  log("LEDS Initialized");
  FastLED.show();
  delay(20);
}

void loopLeds(){ 
  
  // do some state machine magic here
  switch(state){
    case STATE_OK:
      // blend to color
      for(uint16_t i = 0; i < NUM_LEDS; i++) {
        // nice smooth transition
        // TODO: make this configurable
        leds[i] = blend(leds[i], COLOR_OK, COLOR_OK_BLEND_SPEED);
        //leds[i] = c_ok;
      }
      break;
  }
  
  
  if(stateHasChanged){
    //log("stateHasChanged");
    //log(stateHasChanged ? "true" : "false");
    // do something with the state
    switch(state){
      case STATE_STARTUP:
        startup();
        break;
      case STATE_OK:
        log("led response to OK");
        break;
      case STATE_TOUCH:
        // TODO: blend to color
        log("LED response to TOUCH");
        color(COLOR_TOUCH);
        break;
      case STATE_ERROR:
        log("LED response to ERROR");
        color(COLOR_ERROR);
    }
  }
  
  FastLED.show(); // display this frame
  FastLED.delay(1000 / FRAMES_PER_SECOND);
}

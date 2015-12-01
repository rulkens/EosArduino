/* LED SETTINGS */
#define DATA_PIN                     6
#define CHIPSET                      NEOPIXEL
#define NUM_LEDS                     12

/* BLENDING SETTINGS */
// blends the ok color 
#define COLOR_OK_BLEND_SPEED         10
#define COLOR_ERROR_BLEND_SPEED      7
#define COLOR_PROG_RUN_BLEND_SPEED   10
#define COLOR_LONG_TOUCH_BLEND_SPEED 3

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
      break;
    case STATE_OK:
      // blend to color
      // nice smooth transition
      blendLeds(COLOR_OK, COLOR_OK_BLEND_SPEED);
      // TODO: make this configurable
      break;
      
    case STATE_ERROR:
      blendLeds(COLOR_ERROR, COLOR_ERROR_BLEND_SPEED);
      break;
      
    case STATE_PROG_RUN:
      blendLeds(COLOR_PROG_RUN, COLOR_PROG_RUN_BLEND_SPEED);
      break;
      
    case STATE_TOUCH:
      // blend to long tap
      blendLeds(COLOR_LONG_TOUCH, COLOR_LONG_TOUCH_BLEND_SPEED);
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
        //color(COLOR_ERROR);
    }
  }
  
  FastLED.show(); // display this frame
  FastLED.delay(1000 / FRAMES_PER_SECOND);
}

void blendLeds(CRGB to_color, int amount){
  for(uint16_t i = 0; i < NUM_LEDS; i++) {
    leds[i] = blend(leds[i], to_color, amount);
  }
}

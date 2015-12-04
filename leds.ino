
#define FRAMES_PER_SECOND               100

int breathe_timer = 0;

void initLeds() {
  FastLED.addLeds<CHIPSET, DATA_PIN>(leds, NUM_LEDS).setCorrection( TypicalLEDStrip );
  FastLED.setBrightness( BRIGHTNESS );
  
  log("LEDS Initialized");
  FastLED.show();
  delay(20);
}

void loopLeds(){
  
  applyTouchState();
  
  // only apply the normal animations and states when not touching
  if(touch_state == 0){
    breathe_timer++;
    animateState();
    applyState();
  }
  
  FastLED.show(); // display this frame
  FastLED.delay(1000 / FRAMES_PER_SECOND);
}

void applyTouchState(){
  // ANIMATE BASED ON TOUCH
  
  // immediate actions first
  if(touchStateHasChanged){
    // reset breathe timer
    breathe_timer = 0;
    FastLED.setBrightness(255);
    
    switch(touch_state){
      case S_TOUCH_ON:
        // set color directly
        color(COLOR_TOUCH);
        break;
    }
  } else {
    // blending actions
    switch(touch_state){
      case S_TOUCH_ON:
        blendLeds(COLOR_LONG_TOUCH, COLOR_LONG_TOUCH_BLEND_SPEED);
        break;
      case S_TOUCH_LONG:
        // blend to xtra long tap
        blendLeds(COLOR_XLONG_TOUCH, COLOR_XLONG_TOUCH_BLEND_SPEED);
        break;
    }
  }
}

void animateState(){
  // ANIMATE BASED ON STATE
  
  // do some state machine magic here
  switch(state){
      break;
    case STATE_OK:
      // blend to color
      // nice smooth transition
      blendLeds(COLOR_OK, COLOR_OK_BLEND_SPEED);

      // breathing animation
      if(breathe_timer > 600) {
        // calculate brightness
        int brightness = constrain(int(175.0 + 80.0 * sin((double(breathe_timer) / 1800.0) * 2.0 * PI)), 0, 255);
        FastLED.setBrightness(brightness);
      }
      // TODO: make this configurable
      break;
      
    case STATE_ERROR:
      blendLeds(COLOR_ERROR, COLOR_ERROR_BLEND_SPEED);
      break;
      
    case STATE_PROG_RUN:
      blendLeds(COLOR_PROG_RUN, COLOR_PROG_RUN_BLEND_SPEED);
      break;
      
    case STATE_STANDBY:
      blendLeds(COLOR_STANDBY, COLOR_STANDBY_BLEND_SPEED);
      break;
  }
}

void applyState(){
  if(stateHasChanged){
    // reset breathe timer
    breathe_timer = 0;
    FastLED.setBrightness(255);
    // do something with the state
    switch(state){
      case STATE_STARTUP:
        startup();
        break;
      case STATE_OK:
        log("led response to OK");
        break;
      case STATE_ERROR:
        log("LED response to ERROR");
    }
  }
}

void blendLeds(CRGB to_color, int amount){
  for(uint16_t i = 0; i < NUM_LEDS; i++) {
    leds[i] = blend(leds[i], to_color, amount);
  }
}

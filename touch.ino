
int touch_state_old;       // previous touch state
int ms_touching;           // the amount of ms we are touching
int touch_start_ms;
int time_since_touched;    // the amount of time since the last touch
int last_touched;          // the time in ms when last touched
boolean hasDoubleTapped;   // if the state is already double tapped
Adafruit_CAP1188 cap;

void initTouch() {
  
  cap = Adafruit_CAP1188(CAP1188_RESET);
  delay(1000);
  // Initialize the sensor, if using i2c you can pass in the i2c address
  // if (!cap.begin(0x28)) {
  if (!cap.begin(CAP_I2C_PORT)) {
    log("ERROR: Capacitive sensor not found");
    // hang??
    while(1);
  }

  touch_state = 0;
  touch_start_ms = millis();
  hasDoubleTapped = false;
  log("Capacitive sensor Initialized");
  
  delay(20);
}

void loopTouch() {
  uint8_t touched = cap.touched();

  if (touched != 0) {
    // we have a touch!
    
    if(touch_state == S_TOUCH_OFF){
      // record the old state so we can get back to it
      touch_start_ms = millis();
    }
    
    // set the millis since we began
    ms_touching = millis() - touch_start_ms;
    
    // set the three different touch state dependent on the time
    if (ms_touching <= TOUCH_LONG_TIME){
      setTouchState(S_TOUCH_ON);
    } else if (ms_touching > TOUCH_LONG_TIME && ms_touching <= TOUCH_XLONG_TIME){
      // getting into the long touch state
      setTouchState(S_TOUCH_LONG);
    } else if (ms_touching > TOUCH_XLONG_TIME){
      // getting into the extra long touch state
      setTouchState(S_TOUCH_XLONG);
    }
    
    time_since_touched = millis() - last_touched;
    
    // check double tap
    if(time_since_touched < DOUBLE_TAP_TIME && !hasDoubleTapped){
      // double tap event!
      event(EVENT_DOUBLE_TAP, time_since_touched);
      hasDoubleTapped = true;
    }
    
    if(time_since_touched >= DOUBLE_TAP_TIME) {
      // reset double tap trigger
      hasDoubleTapped = false;
    }
    return;
    
  } else {
    // no touch detected
    if(touch_state != S_TOUCH_OFF){
      // switch state and show it!
      
      setTouchState(S_TOUCH_OFF);
      
      if(ms_touching < TAP_TIME){
        // fire a tap event
        event(EVENT_TAP, ms_touching);
      }
      
      // update the moment it's last touched
      last_touched = millis();
    }
  }
}

/**
gets executed at the end of the loop, make sure to set any dirty flags to false
**/
void endLoopTouch() {
  touchStateHasChanged = false;
}

/**
sets the touch state and fire off an event to inform people the universe has changed
**/
void setTouchState(int state){
  if(state == touch_state) return;
  event(EVENT_TOUCH, touch_state, touch_state_old);
  touch_state_old = touch_state;
  touch_state = state;
  touchStateHasChanged = true;
}

/* CAPACITIVE TOUCH SETTINGS */
// Reset Pin is used for I2C or SPI
#define CAP1188_RESET      9
#define CAP_I2C_PORT       0x29

/* TOUCH STATES */
#define S_TOUCH_ON     1
#define S_TOUCH_OFF    0
#define S_TOUCH_LONG   2
#define S_TOUCH_XLONG  3

/* TOUCH EVENTS */
#define EVENT_TOUCH        "touch"
#define EVENT_TOUCH_LONG   "touchlong"
#define EVENT_TAP          "tap"
#define EVENT_DOUBLE_TAP   "doubletap"

#define TOUCH_LONG_TIME    1200 // the time in ms before a touch is registered as long
#define TOUCH_XLONG_TIME   4000 // the time in ms before a touch is registered as extra long
#define DOUBLE_TAP_TIME    600 // the interval between two taps, lower than this is registered as a double tap

int touch_state;
int state_before_touch;
int ms_touching;           // the amount of ms we are touching
int touch_start_ms;
int time_since_touched; // the amount of time since the last touch
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
      touch_state = S_TOUCH_ON;
      event(EVENT_TOUCH, S_TOUCH_ON);
      // record the old state so we can get back to it
      state_before_touch = getState();
      touch_start_ms = millis();
      setState(STATE_TOUCH);
    }
    
    // set the millis since we began
    ms_touching = millis() - touch_start_ms;
    //log(ms_touching);
    
    if (ms_touching > TOUCH_LONG_TIME && ms_touching <= TOUCH_XLONG_TIME && touch_state != S_TOUCH_LONG){
      // getting into the long touch state
      // fire an event
      touch_state = S_TOUCH_LONG;
      setState(STATE_TOUCH_LONG);
      event(EVENT_TOUCH, touch_state);
    }
    
    if (ms_touching > TOUCH_XLONG_TIME && touch_state != S_TOUCH_XLONG){
      // getting into the long touch state
      // fire an event
      touch_state = S_TOUCH_XLONG;
      setState(STATE_TOUCH_XLONG);
      event(EVENT_TOUCH, touch_state);
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
      
      touch_state = S_TOUCH_OFF;
      last_touched = millis();
      event(EVENT_TOUCH, touch_state);
      // fire a tap event with the length in ms
      event(EVENT_TAP, millis() - last_touched);
      
      // set the state to what it was before touching started
      setState(state_before_touch);
      
      // update the moment it's last touched
      last_touched = millis();
    }
  }
}


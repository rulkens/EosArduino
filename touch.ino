/* CAPACITIVE TOUCH SETTINGS */
// Reset Pin is used for I2C or SPI
#define CAP1188_RESET  9
#define CAP_I2C_PORT 0x29

/* TOUCH STATES */
#define STATE_TOUCH_ON 1
#define STATE_TOUCH_OFF 0

/* TOUCH EVENTS */
#define EVENT_TOUCH "touch"

int touch_state;
int state_before_touch;

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
  log("Capacitive sensor Initialized");
  touch_state = 0;
  delay(20);
}

void loopTouch() {
  uint8_t touched = cap.touched();

  if (touched == 0) {
    if(touch_state != STATE_TOUCH_OFF){
      // switch state and show it!
      
      touch_state = STATE_TOUCH_OFF;
      event(EVENT_TOUCH, STATE_TOUCH_OFF);
      
      // TODO: move this somewhere else
      setState(state_before_touch);
    }
    // No touch detected
    return;
  } else {
  // we have touch down!
    if(touch_state != STATE_TOUCH_ON){
      touch_state = STATE_TOUCH_ON;
      event(EVENT_TOUCH, STATE_TOUCH_ON);
      // record the old state so we can get back to it
      state_before_touch = getState();
      setState(STATE_TOUCH);
    }
  }
}


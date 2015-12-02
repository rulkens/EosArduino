/* CAPACITIVE TOUCH SETTINGS */
// Reset Pin is used for I2C or SPI
#define CAP1188_RESET      9
#define CAP_I2C_PORT       0x29

/* TOUCH EVENTS */
#define EVENT_TOUCH        "touch"
#define EVENT_TAP          "tap"
#define EVENT_DOUBLE_TAP   "doubletap"

#define TOUCH_LONG_TIME    1200 // the time in ms before a touch is registered as long
#define TOUCH_XLONG_TIME   4000 // the time in ms before a touch is registered as extra long
#define DOUBLE_TAP_TIME    600 // the interval between two taps, lower than this is registered as a double tap

#define TAP_TIME           300 // everything shorter than 300 ms is considered a tap

/* TOUCH STATES */
#define S_TOUCH_OFF    0
#define S_TOUCH_ON     1
#define S_TOUCH_LONG   2
#define S_TOUCH_XLONG  3

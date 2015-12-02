
#define STARTUP_TURNS           10
#define BRIGHTNESS              200
#define STARTUP_ANIMATION_DELAY 20

#define NUM_LEDS    12

// startup animation, sort of loading bar
void startup(){
  log("Startup start");
  
  setState(STATE_STARTUP);
  
  uint32_t c = COLOR_WAIT;

  for(uint16_t turn=0; turn < STARTUP_TURNS; turn++) {
    for(uint16_t i=0; i<NUM_LEDS; i++) {
      for(uint16_t j=0; j<NUM_LEDS; j++) {
        boolean on = ((j + i) % NUM_LEDS) <= turn;
        if(on){
          leds[j] = c;
        } else {
          // fade a bit
          leds[j].fadeToBlackBy(140);
        }
        FastLED.show();
      }
      delay(STARTUP_ANIMATION_DELAY);
    }
    FastLED.show();
  }
  log("Startup end");
  setState(STATE_OK);
}

void color(uint32_t c){
  // TODO
  for(uint16_t i = 0; i < NUM_LEDS; i++) {
    leds[i] = c;
  }
}

// Fill the dots one after the other with a color
void colorWipe(uint32_t c, uint8_t wait) {
  for(uint16_t i=0; i<NUM_LEDS; i++) {
    leds[i] = c;
    FastLED.show();
    delay(wait);
  }
}

//void blend(CRGB* items) {
//  for(uint16_t i=0; i<NUM_LEDS; i++) {
//    leds[i] = c;
//    FastLED.show();
//    delay(wait);
//  }
//}

void rainbow(uint8_t wait) {
  uint16_t i, j;

  for(j=0; j<256; j++) {
    for(i=0; i<NUM_LEDS; i++) {
      leds[i] = Wheel((i+j) & 255);
    }
    FastLED.show();
    delay(wait);
  }
}

// Slightly different, this makes the rainbow equally distributed throughout
void rainbowCycle(uint8_t wait) {
  uint16_t i, j;

  for(j=0; j<256*5; j++) { // 5 cycles of all colors on wheel
    for(i=0; i< NUM_LEDS; i++) {
      leds[i] = Wheel(((i * 256 / NUM_LEDS) + j) & 255);
    }
    FastLED.show();
    delay(wait);
  }
}

//Theatre-style crawling lights.
void theaterChase(uint32_t c, uint8_t wait) {
  for (int j=0; j<10; j++) {  //do 10 cycles of chasing
    for (int q=0; q < 3; q++) {
      for (int i=0; i < NUM_LEDS; i=i+3) {
        leds[i+q], c;    //turn every third pixel on
      }
      FastLED.show();

      delay(wait);

      for (int i=0; i < NUM_LEDS; i=i+3) {
        leds[i+q] = 0;        //turn every third pixel off
      }
    }
  }
}

//Theatre-style crawling lights with rainbow effect
void theaterChaseRainbow(uint8_t wait) {
  for (int j=0; j < 256; j++) {     // cycle all 256 colors in the wheel
    for (int q=0; q < 3; q++) {
      for (int i=0; i < NUM_LEDS; i=i+3) {
        leds[i+q] = Wheel( (i+j) % 255);    //turn every third pixel on
      }
      FastLED.show();

      delay(wait);

      for (int i=0; i < NUM_LEDS; i=i+3) {
        leds[i+q] = 0;        //turn every third pixel off
      }
    }
  }
}

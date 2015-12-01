// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Wheel(byte WheelPos) {
  WheelPos = 255 - WheelPos;
  if(WheelPos < 85) {
    //return FastLED.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  }
  if(WheelPos < 170) {
    WheelPos -= 85;
    //return FastLED.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
  WheelPos -= 170;
  //return FastLED.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
  return 0;
}

uint16_t final_color[3];
void Blend(uint16_t color_start[3],uint16_t color_end[3],uint16_t blend_level, uint16_t max_level)
{
     final_color[0] = (uint16_t)(color_start[0] - (blend_level*((color_start[0]-(float)color_end[0])/max_level)));
     final_color[1] = (uint16_t)(color_start[1] - (blend_level*((color_start[1]-(float)color_end[1])/max_level)));
     final_color[2] = (uint16_t)(color_start[2] - (blend_level*((color_start[2]-(float)color_end[2])/max_level)));
}

unsigned long hex2int(const char *a, unsigned int len){
   int i;
   unsigned long val = 0;

   for(i=0;i<len;i++)
      if(a[i] <= 57)
       val += (a[i]-48)*(1<<(4*(len-1-i)));
      else
       val += (a[i]-55)*(1<<(4*(len-1-i)));
   return val;
}

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_I2C_ADDR 0x3C
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RST_PIN -1

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RST_PIN);

#define FRAME_DELAY (42)
#define FRAME_COUNT (sizeof(frames) / sizeof(frames[0]))
#define FRAME_WIDTH 64
#define FRAME_HEIGHT 64

// Substitua esta parte do código com os frames reais da animação
const byte PROGMEM frames[][512] = {
   {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,24,0,0,0,0,0,0,0,28,0,0,0,0,0,0,0,60,0,0,0,0,0,0,0,60,0,0,0,0,0,0,0,60,0,0,0,0,0,0,0,60,0,0,0,0,0,0,0,60,0,0,0,0,0,0,0,126,0,0,0,0,0,0,0,126,0,0,0,0,0,0,0,110,0,0,0,0,0,0,0,110,0,0,0,0,0,0,0,230,0,0,0,0,0,0,0,230,0,0,0,0,0,0,0,231,0,0,0,0,0,1,192,199,0,96,0,0,0,1,192,199,0,112,0,0,0,3,225,199,0,240,0,0,0,3,225,195,0,248,0,0,0,7,225,131,0,248,0,0,0,7,113,131,129,248,0,0,0,14,115,131,129,220,0,0,15,254,51,131,129,156,31,240,15,252,59,131,131,140,63,240,15,252,59,1,131,142,127,240,0,0,31,1,131,142,112,0,0,0,31,1,195,7,224,0,0,0,31,1,199,7,192,0,0,0,14,1,199,7,192,0,0,0,14,1,198,3,128,0,0,0,6,0,206,3,0,0,0,0,0,0,206,0,0,0,0,0,0,0,236,0,0,0,0,0,0,0,252,0,0,0,0,0,0,0,252,0,0,0,0,0,0,0,248,0,0,0,0,0,0,0,120,0,0,0,0,0,0,0,120,0,0,0,0,0,0,0,112,0,0,0,0,0,0,0,112,0,0,0,0,0,0,0,112,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,24,0,0,0,0,0,0,0,28,0,0,0,0,0,0,0,60,0,0,0,0,0,0,0,60,0,0,0,0,0,0,0,60,0,0,0,0,0,0,0,60,0,0,0,0,0,0,0,60,0,0,0,0,0,0,0,126,0,0,0,0,0,0,0,126,0,0,0,0,0,0,0,110,0,0,0,0,0,0,0,110,0,0,0,0,0,0,0,230,0,0,0,0,0,0,0,230,0,0,0,0,0,0,0,231,0,0,0,0,0,1,192,199,0,96,0,0,0,1,192,199,0,112,0,0,0,3,225,199,0,240,0,0,0,3,225,195,0,248,0,0,0,7,225,131,0,248,0,0,0,7,113,131,129,248,0,0,0,14,115,131,129,220,0,0,15,254,51,131,129,156,31,240,15,252,59,131,131,140,63,240,15,252,59,1,131,142,127,240,0,0,31,1,131,142,112,0,0,0,31,1,195,7,224,0,0,0,31,1,199,7,192,0,0,0,14,1,199,7,192,0,0,0,14,1,198,3,128,0,0,0,6,0,206,3,0,0,0,0,0,0,206,0,0,0,0,0,0,0,236,0,0,0,0,0,0,0,252,0,0,0,0,0,0,0,252,0,0,0,0,0,0,0,248,0,0,0,0,0,0,0,120,0,0,0,0,0,0,0,120,0,0,0,0,0,0,0,112,0,0,0,0,0,0,0,112,0,0,0,0,0,0,0,112,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,24,0,0,0,0,0,0,0,28,0,0,0,0,0,0,0,60,0,0,0,0,0,0,0,60,0,0,0,0,0,0,0,60,0,0,0,0,0,0,0,60,0,0,0,0,0,0,0,60,0,0,0,0,0,0,0,126,0,0,0,0,0,0,0,126,0,0,0,0,0,0,0,110,0,0,0,0,0,0,0,110,0,0,0,0,0,0,0,230,0,0,0,0,0,0,0,230,0,0,0,0,0,0,0,231,0,0,0,0,0,1,192,199,0,96,0,0,0,1,192,199,0,112,0,0,0,3,225,199,0,240,0,0,0,3,225,195,0,248,0,0,0,7,225,131,0,248,0,0,0,7,113,131,129,248,0,0,0,14,115,131,129,220,0,0,15,254,51,131,129,156,31,240,15,252,59,131,131,140,63,240,15,252,59,1,131,142,127,240,0,0,31,1,131,142,112,0,0,0,31,1,195,7,224,0,0,0,31,1,199,7,192,0,0,0,14,1,199,7,192,0,0,0,14,1,198,3,128,0,0,0,6,0,206,3,0,0,0,0,0,0,206,0,0,0,0,0,0,0,236,0,0,0,0,0,0,0,252,0,0,0,0,0,0,0,252,0,0,0,0,0,0,0,248,0,0,0,0,0,0,0,120,0,0,0,0,0,0,0,120,0,0,0,0,0,0,0,112,0,0,0,0,0,0,0,112,0,0,0,0,0,0,0,112,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,24,0,0,0,0,0,0,0,28,0,0,0,0,0,0,0,60,0,0,0,0,0,0,0,60,0,0,0,0,0,0,0,60,0,0,0,0,0,0,0,60,0,0,0,0,0,0,0,60,0,0,0,0,0,0,0,126,0,0,0,0,0,0,0,126,0,0,0,0,0,0,0,110,0,0,0,0,0,0,0,110,0,0,0,0,0,0,0,230,0,0,0,0,0,0,0,230,0,0,0,0,0,0,0,231,0,0,0,0,0,1,192,199,0,96,0,0,0,1,192,199,0,112,0,0,0,3,225,199,0,240,0,0,0,3,225,195,0,248,0,0,0,7,225,131,0,248,0,0,0,7,113,131,129,248,0,0,0,14,115,131,129,220,0,0,15,254,51,131,129,156,31,240,15,252,59,131,131,140,63,240,15,252,59,1,131,142,127,240,0,0,31,1,131,142,112,0,0,0,31,1,195,7,224,0,0,0,31,1,199,7,192,0,0,0,14,1,199,7,192,0,0,0,14,1,198,3,128,0,0,0,6,0,206,3,0,0,0,0,0,0,206,0,0,0,0,0,0,0,236,0,0,0,0,0,0,0,252,0,0,0,0,0,0,0,252,0,0,0,0,0,0,0,248,0,0,0,0,0,0,0,120,0,0,0,0,0,0,0,120,0,0,0,0,0,0,0,112,0,0,0,0,0,0,0,112,0,0,0,0,0,0,0,112,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,24,0,0,0,0,0,0,0,28,0,0,0,0,0,0,0,60,0,0,0,0,0,0,0,60,0,0,0,0,0,0,0,60,0,0,0,0,0,0,0,60,0,0,0,0,0,0,0,60,0,0,0,0,0,0,0,126,0,0,0,0,0,0,0,126,0,0,0,0,0,0,0,110,0,0,0,0,0,0,0,110,0,0,0,0,0,0,0,230,0,0,0,0,0,0,0,230,0,0,0,0,0,0,0,231,0,0,0,0,0,1,192,199,0,96,0,0,0,1,192,199,0,112,0,0,0,3,225,199,0,240,0,0,0,3,225,195,0,248,0,0,0,7,225,131,0,248,0,0,0,7,113,131,129,248,0,0,0,14,115,131,129,220,0,0,1,254,51,131,129,156,31,240,3,252,59,131,131,140,63,240,1,252,59,1,131,142,127,240,0,0,31,1,131,142,112,0,0,0,31,1,195,7,224,0,0,0,31,1,199,7,192,0,0,0,14,1,199,7,192,0,0,0,14,1,198,3,128,0,0,0,6,0,206,3,0,0,0,0,0,0,206,0,0,0,0,0,0,0,236,0,0,0,0,0,0,0,252,0,0,0,0,0,0,0,252,0,0,0,0,0,0,0,248,0,0,0,0,0,0,0,120,0,0,0,0,0,0,0,120,0,0,0,0,0,0,0,112,0,0,0,0,0,0,0,112,0,0,0,0,0,0,0,112,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,24,0,0,0,0,0,0,0,28,0,0,0,0,0,0,0,60,0,0,0,0,0,0,0,60,0,0,0,0,0,0,0,60,0,0,0,0,0,0,0,60,0,0,0,0,0,0,0,60,0,0,0,0,0,0,0,126,0,0,0,0,0,0,0,126,0,0,0,0,0,0,0,110,0,0,0,0,0,0,0,110,0,0,0,0,0,0,0,230,0,0,0,0,0,0,0,230,0,0,0,0,0,0,0,231,0,0,0,0,0,1,192,199,0,96,0,0,0,1,192,199,0,112,0,0,0,3,225,199,0,240,0,0,0,3,225,195,0,248,0,0,0,7,225,131,0,248,0,0,0,7,113,131,129,248,0,0,0,14,115,131,129,220,0,0,0,14,51,131,129,156,31,240,0,12,59,131,131,140,63,240,0,0,59,1,131,142,127,240,0,0,31,1,131,142,112,0,0,0,31,1,195,7,224,0,0,0,31,1,199,7,192,0,0,0,14,1,199,7,192,0,0,0,14,1,198,3,128,0,0,0,6,0,206,3,0,0,0,0,0,0,206,0,0,0,0,0,0,0,236,0,0,0,0,0,0,0,252,0,0,0,0,0,0,0,252,0,0,0,0,0,0,0,248,0,0,0,0,0,0,0,120,0,0,0,0,0,0,0,120,0,0,0,0,0,0,0,112,0,0,0,0,0,0,0,112,0,0,0,0,0,0,0,112,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,24,0,0,0,0,0,0,0,28,0,0,0,0,0,0,0,60,0,0,0,0,0,0,0,60,0,0,0,0,0,0,0,60,0,0,0,0,0,0,0,60,0,0,0,0,0,0,0,60,0,0,0,0,0,0,0,126,0,0,0,0,0,0,0,126,0,0,0,0,0,0,0,110,0,0,0,0,0,0,0,110,0,0,0,0,0,0,0,230,0,0,0,0,0,0,0,230,0,0,0,0,0,0,0,231,0,0,0,0,0,0,0,199,0,96,0,0,0,0,64,199,0,112,0,0,0,0,225,199,0,240,0,0,0,0,225,195,0,248,0,0,0,0,97,131,0,248,0,0,0,0,113,131,129,248,0,0,0,0,115,131,129,220,0,0,0,0,51,131,129,156,31,240,0,0,59,131,131,140,63,240,0,0,59,1,131,142,127,240,0,0,31,1,131,142,112,0,0,0,31,1,195,7,224,0,0,0,31,1,199,7,192,0,0,0,14,1,199,7,192,0,0,0,14,1,198,3,128,0,0,0,6,0,206,3,0,0,0,0,0,0,206,0,0,0,0,0,0,0,236,0,0,0,0,0,0,0,252,0,0,0,0,0,0,0,252,0,0,0,0,0,0,0,248,0,0,0,0,0,0,0,120,0,0,0,0,0,0,0,120,0,0,0,0,0,0,0,112,0,0,0,0,0,0,0,112,0,0,0,0,0,0,0,112,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,24,0,0,0,0,0,0,0,28,0,0,0,0,0,0,0,60,0,0,0,0,0,0,0,60,0,0,0,0,0,0,0,60,0,0,0,0,0,0,0,60,0,0,0,0,0,0,0,60,0,0,0,0,0,0,0,126,0,0,0,0,0,0,0,126,0,0,0,0,0,0,0,110,0,0,0,0,0,0,0,110,0,0,0,0,0,0,0,230,0,0,0,0,0,0,0,230,0,0,0,0,0,0,0,231,0,0,0,0,0,0,0,199,0,96,0,0,0,0,0,199,0,112,0,0,0,0,1,199,0,240,0,0,0,0,1,195,0,248,0,0,0,0,1,131,0,248,0,0,0,0,1,131,129,248,0,0,0,0,3,131,129,220,0,0,0,0,3,131,129,156,31,240,0,0,3,131,131,140,63,240,0,0,3,1,131,142,127,240,0,0,7,1,131,142,112,0,0,0,7,1,195,7,224,0,0,0,7,1,199,7,192,0,0,0,6,1,199,7,192,0,0,0,6,1,198,3,128,0,0,0,6,0,206,3,0,0,0,0,0,0,206,0,0,0,0,0,0,0,236,0,0,0,0,0,0,0,252,0,0,0,0,0,0,0,252,0,0,0,0,0,0,0,248,0,0,0,0,0,0,0,120,0,0,0,0,0,0,0,120,0,0,0,0,0,0,0,112,0,0,0,0,0,0,0,112,0,0,0,0,0,0,0,112,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,24,0,0,0,0,0,0,0,28,0,0,0,0,0,0,0,60,0,0,0,0,0,0,0,60,0,0,0,0,0,0,0,60,0,0,0,0,0,0,0,60,0,0,0,0,0,0,0,60,0,0,0,0,0,0,0,126,0,0,0,0,0,0,0,126,0,0,0,0,0,0,0,110,0,0,0,0,0,0,0,110,0,0,0,0,0,0,0,230,0,0,0,0,0,0,0,230,0,0,0,0,0,0,0,199,0,0,0,0,0,0,0,7,0,96,0,0,0,0,0,7,0,112,0,0,0,0,0,7,0,240,0,0,0,0,0,3,0,248,0,0,0,0,0,3,0,248,0,0,0,0,0,3,129,248,0,0,0,0,0,3,129,220,0,0,0,0,0,3,129,156,31,240,0,0,0,3,131,140,63,240,0,0,0,1,131,142,127,240,0,0,0,1,131,142,112,0,0,0,0,1,195,7,224,0,0,0,0,1,199,7,192,0,0,0,0,1,199,7,192,0,0,0,0,1,198,3,128,0,0,0,0,0,206,3,0,0,0,0,0,0,206,0,0,0,0,0,0,0,236,0,0,0,0,0,0,0,252,0,0,0,0,0,0,0,252,0,0,0,0,0,0,0,248,0,0,0,0,0,0,0,120,0,0,0,0,0,0,0,120,0,0,0,0,0,0,0,112,0,0,0,0,0,0,0,112,0,0,0,0,0,0,0,112,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,12,0,0,0,0,0,0,0,14,0,0,0,0,0,0,0,14,0,0,0,0,0,0,0,14,0,0,0,0,0,0,0,14,0,0,0,0,0,0,0,6,0,0,0,0,0,0,0,6,0,0,0,0,0,0,0,7,0,0,0,0,0,0,0,7,0,96,0,0,0,0,0,7,0,112,0,0,0,0,0,7,0,240,0,0,0,0,0,3,0,248,0,0,0,0,0,3,0,248,0,0,0,0,0,3,129,248,0,0,0,0,0,3,129,220,0,0,0,0,0,3,129,156,31,240,0,0,0,3,131,140,63,240,0,0,0,1,131,142,127,240,0,0,0,1,131,142,112,0,0,0,0,1,195,7,224,0,0,0,0,1,199,7,192,0,0,0,0,1,199,7,192,0,0,0,0,1,198,3,128,0,0,0,0,0,206,3,0,0,0,0,0,0,206,0,0,0,0,0,0,0,236,0,0,0,0,0,0,0,252,0,0,0,0,0,0,0,252,0,0,0,0,0,0,0,248,0,0,0,0,0,0,0,120,0,0,0,0,0,0,0,120,0,0,0,0,0,0,0,112,0,0,0,0,0,0,0,112,0,0,0,0,0,0,0,112,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,96,0,0,0,0,0,0,0,112,0,0,0,0,0,0,0,240,0,0,0,0,0,0,0,248,0,0,0,0,0,0,0,248,0,0,0,0,0,0,1,248,0,0,0,0,0,0,1,220,0,0,0,0,0,0,1,156,31,240,0,0,0,0,3,140,63,240,0,0,0,0,3,142,127,240,0,0,0,0,3,142,112,0,0,0,0,0,3,7,224,0,0,0,0,0,7,7,192,0,0,0,0,0,199,7,192,0,0,0,0,0,198,3,128,0,0,0,0,0,206,3,0,0,0,0,0,0,206,0,0,0,0,0,0,0,236,0,0,0,0,0,0,0,252,0,0,0,0,0,0,0,252,0,0,0,0,0,0,0,248,0,0,0,0,0,0,0,120,0,0,0,0,0,0,0,120,0,0,0,0,0,0,0,112,0,0,0,0,0,0,0,112,0,0,0,0,0,0,0,112,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,96,0,0,0,0,0,0,0,112,0,0,0,0,0,0,0,240,0,0,0,0,0,0,0,248,0,0,0,0,0,0,0,248,0,0,0,0,0,0,1,248,0,0,0,0,0,0,1,220,0,0,0,0,0,0,1,156,31,240,0,0,0,0,1,140,63,240,0,0,0,0,3,142,127,240,0,0,0,0,3,142,112,0,0,0,0,0,3,7,224,0,0,0,0,0,7,7,192,0,0,0,0,0,7,7,192,0,0,0,0,0,6,3,128,0,0,0,0,0,0,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,31,240,0,0,0,0,0,0,63,240,0,0,0,0,0,6,127,240,0,0,0,0,0,14,112,0,0,0,0,0,0,7,224,0,0,0,0,0,0,7,192,0,0,0,0,0,0,7,192,0,0,0,0,0,0,3,128,0,0,0,0,0,0,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,192,0,0,0,0,0,0,1,192,0,0,0,0,0,0,3,224,0,0,0,0,0,0,3,224,0,0,0,0,0,0,7,224,0,0,0,0,0,0,7,64,0,0,0,0,0,0,14,0,0,0,0,0,0,15,254,0,0,0,0,0,0,15,252,0,0,0,0,0,0,15,252,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,192,0,0,0,0,0,0,1,192,0,0,0,0,0,0,3,224,0,0,0,0,0,0,3,225,128,0,0,0,0,0,7,225,128,0,0,0,0,0,7,113,128,0,0,0,0,0,14,115,128,0,0,0,0,15,254,51,128,0,0,0,0,15,252,59,128,0,0,0,0,15,252,59,0,0,0,0,0,0,0,31,0,0,0,0,0,0,0,31,0,0,0,0,0,0,0,31,0,0,0,0,0,0,0,14,0,0,0,0,0,0,0,14,0,0,0,0,0,0,0,6,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,24,0,0,0,0,0,0,0,28,0,0,0,0,0,0,0,60,0,0,0,0,0,0,0,60,0,0,0,0,0,0,0,60,0,0,0,0,0,0,0,60,0,0,0,0,0,0,0,60,0,0,0,0,0,0,0,112,0,0,0,0,0,0,0,112,0,0,0,0,0,0,0,96,0,0,0,0,0,0,0,96,0,0,0,0,0,0,0,224,0,0,0,0,0,0,0,224,0,0,0,0,0,0,0,224,0,0,0,0,0,1,192,192,0,0,0,0,0,1,192,192,0,0,0,0,0,3,225,192,0,0,0,0,0,3,225,192,0,0,0,0,0,7,225,128,0,0,0,0,0,7,113,128,0,0,0,0,0,14,115,128,0,0,0,0,15,254,51,128,0,0,0,0,15,252,59,128,0,0,0,0,15,252,59,0,0,0,0,0,0,0,31,0,0,0,0,0,0,0,31,0,0,0,0,0,0,0,31,0,0,0,0,0,0,0,14,0,0,0,0,0,0,0,14,0,0,0,0,0,0,0,6,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,24,0,0,0,0,0,0,0,28,0,0,0,0,0,0,0,60,0,0,0,0,0,0,0,60,0,0,0,0,0,0,0,60,0,0,0,0,0,0,0,60,0,0,0,0,0,0,0,60,0,0,0,0,0,0,0,126,0,0,0,0,0,0,0,126,0,0,0,0,0,0,0,110,0,0,0,0,0,0,0,110,0,0,0,0,0,0,0,230,0,0,0,0,0,0,0,230,0,0,0,0,0,0,0,231,0,0,0,0,0,1,192,199,0,0,0,0,0,1,192,199,0,0,0,0,0,3,225,199,0,0,0,0,0,3,225,195,0,0,0,0,0,7,225,131,0,0,0,0,0,7,113,131,128,0,0,0,0,14,115,131,128,0,0,0,15,254,51,131,128,0,0,0,15,252,59,131,128,0,0,0,15,252,59,1,128,0,0,0,0,0,31,1,128,0,0,0,0,0,31,1,192,0,0,0,0,0,31,1,192,0,0,0,0,0,14,0,128,0,0,0,0,0,14,0,0,0,0,0,0,0,6,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,24,0,0,0,0,0,0,0,28,0,0,0,0,0,0,0,60,0,0,0,0,0,0,0,60,0,0,0,0,0,0,0,60,0,0,0,0,0,0,0,60,0,0,0,0,0,0,0,60,0,0,0,0,0,0,0,126,0,0,0,0,0,0,0,126,0,0,0,0,0,0,0,110,0,0,0,0,0,0,0,110,0,0,0,0,0,0,0,230,0,0,0,0,0,0,0,230,0,0,0,0,0,0,0,231,0,0,0,0,0,1,192,199,0,0,0,0,0,1,192,199,0,0,0,0,0,3,225,199,0,0,0,0,0,3,225,195,0,0,0,0,0,7,225,131,0,0,0,0,0,7,113,131,128,0,0,0,0,14,115,131,128,0,0,0,15,254,51,131,128,0,0,0,15,252,59,131,128,0,0,0,15,252,59,1,128,0,0,0,0,0,31,1,128,0,0,0,0,0,31,1,192,0,0,0,0,0,31,1,192,0,0,0,0,0,14,1,192,0,0,0,0,0,14,1,192,0,0,0,0,0,6,0,192,0,0,0,0,0,0,0,192,0,0,0,0,0,0,0,224,0,0,0,0,0,0,0,252,0,0,0,0,0,0,0,252,0,0,0,0,0,0,0,248,0,0,0,0,0,0,0,120,0,0,0,0,0,0,0,120,0,0,0,0,0,0,0,112,0,0,0,0,0,0,0,112,0,0,0,0,0,0,0,112,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,24,0,0,0,0,0,0,0,28,0,0,0,0,0,0,0,60,0,0,0,0,0,0,0,60,0,0,0,0,0,0,0,60,0,0,0,0,0,0,0,60,0,0,0,0,0,0,0,60,0,0,0,0,0,0,0,126,0,0,0,0,0,0,0,126,0,0,0,0,0,0,0,110,0,0,0,0,0,0,0,110,0,0,0,0,0,0,0,230,0,0,0,0,0,0,0,230,0,0,0,0,0,0,0,231,0,0,0,0,0,1,192,199,0,0,0,0,0,1,192,199,0,0,0,0,0,3,225,199,0,64,0,0,0,3,225,195,0,224,0,0,0,7,225,131,0,192,0,0,0,7,113,131,129,192,0,0,0,14,115,131,129,192,0,0,15,254,51,131,129,192,0,0,15,252,59,131,129,128,0,0,15,252,59,1,131,128,0,0,0,0,31,1,131,128,0,0,0,0,31,1,195,0,0,0,0,0,31,1,199,0,0,0,0,0,14,1,199,0,0,0,0,0,14,1,198,0,0,0,0,0,6,0,206,0,0,0,0,0,0,0,206,0,0,0,0,0,0,0,236,0,0,0,0,0,0,0,252,0,0,0,0,0,0,0,252,0,0,0,0,0,0,0,248,0,0,0,0,0,0,0,120,0,0,0,0,0,0,0,120,0,0,0,0,0,0,0,112,0,0,0,0,0,0,0,112,0,0,0,0,0,0,0,112,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,24,0,0,0,0,0,0,0,28,0,0,0,0,0,0,0,60,0,0,0,0,0,0,0,60,0,0,0,0,0,0,0,60,0,0,0,0,0,0,0,60,0,0,0,0,0,0,0,60,0,0,0,0,0,0,0,126,0,0,0,0,0,0,0,126,0,0,0,0,0,0,0,110,0,0,0,0,0,0,0,110,0,0,0,0,0,0,0,230,0,0,0,0,0,0,0,230,0,0,0,0,0,0,0,231,0,0,0,0,0,1,192,199,0,96,0,0,0,1,192,199,0,112,0,0,0,3,225,199,0,240,0,0,0,3,225,195,0,248,0,0,0,7,225,131,0,248,0,0,0,7,113,131,129,248,0,0,0,14,115,131,129,220,0,0,15,254,51,131,129,156,0,0,15,252,59,131,131,140,0,0,15,252,59,1,131,142,0,0,0,0,31,1,131,142,0,0,0,0,31,1,195,6,0,0,0,0,31,1,199,0,0,0,0,0,14,1,199,0,0,0,0,0,14,1,198,0,0,0,0,0,6,0,206,0,0,0,0,0,0,0,206,0,0,0,0,0,0,0,236,0,0,0,0,0,0,0,252,0,0,0,0,0,0,0,252,0,0,0,0,0,0,0,248,0,0,0,0,0,0,0,120,0,0,0,0,0,0,0,120,0,0,0,0,0,0,0,112,0,0,0,0,0,0,0,112,0,0,0,0,0,0,0,112,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,24,0,0,0,0,0,0,0,28,0,0,0,0,0,0,0,60,0,0,0,0,0,0,0,60,0,0,0,0,0,0,0,60,0,0,0,0,0,0,0,60,0,0,0,0,0,0,0,60,0,0,0,0,0,0,0,126,0,0,0,0,0,0,0,126,0,0,0,0,0,0,0,110,0,0,0,0,0,0,0,110,0,0,0,0,0,0,0,230,0,0,0,0,0,0,0,230,0,0,0,0,0,0,0,231,0,0,0,0,0,1,192,199,0,96,0,0,0,1,192,199,0,112,0,0,0,3,225,199,0,240,0,0,0,3,225,195,0,248,0,0,0,7,225,131,0,248,0,0,0,7,113,131,129,248,0,0,0,14,115,131,129,220,0,0,15,254,51,131,129,156,0,0,15,252,59,131,131,140,32,0,15,252,59,1,131,142,112,0,0,0,31,1,131,142,240,0,0,0,31,1,195,7,224,0,0,0,31,1,199,7,192,0,0,0,14,1,199,7,192,0,0,0,14,1,198,3,128,0,0,0,6,0,206,3,0,0,0,0,0,0,206,0,0,0,0,0,0,0,236,0,0,0,0,0,0,0,252,0,0,0,0,0,0,0,252,0,0,0,0,0,0,0,248,0,0,0,0,0,0,0,120,0,0,0,0,0,0,0,120,0,0,0,0,0,0,0,112,0,0,0,0,0,0,0,112,0,0,0,0,0,0,0,112,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,24,0,0,0,0,0,0,0,28,0,0,0,0,0,0,0,60,0,0,0,0,0,0,0,60,0,0,0,0,0,0,0,60,0,0,0,0,0,0,0,60,0,0,0,0,0,0,0,60,0,0,0,0,0,0,0,126,0,0,0,0,0,0,0,126,0,0,0,0,0,0,0,110,0,0,0,0,0,0,0,110,0,0,0,0,0,0,0,230,0,0,0,0,0,0,0,230,0,0,0,0,0,0,0,231,0,0,0,0,0,1,192,199,0,96,0,0,0,1,192,199,0,112,0,0,0,3,225,199,0,240,0,0,0,3,225,195,0,248,0,0,0,7,225,131,0,248,0,0,0,7,113,131,129,248,0,0,0,14,115,131,129,220,0,0,15,254,51,131,129,156,31,128,15,252,59,131,131,140,63,192,15,252,59,1,131,142,127,128,0,0,31,1,131,142,112,0,0,0,31,1,195,7,224,0,0,0,31,1,199,7,192,0,0,0,14,1,199,7,192,0,0,0,14,1,198,3,128,0,0,0,6,0,206,3,0,0,0,0,0,0,206,0,0,0,0,0,0,0,236,0,0,0,0,0,0,0,252,0,0,0,0,0,0,0,252,0,0,0,0,0,0,0,248,0,0,0,0,0,0,0,120,0,0,0,0,0,0,0,120,0,0,0,0,0,0,0,112,0,0,0,0,0,0,0,112,0,0,0,0,0,0,0,112,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,24,0,0,0,0,0,0,0,28,0,0,0,0,0,0,0,60,0,0,0,0,0,0,0,60,0,0,0,0,0,0,0,60,0,0,0,0,0,0,0,60,0,0,0,0,0,0,0,60,0,0,0,0,0,0,0,126,0,0,0,0,0,0,0,126,0,0,0,0,0,0,0,110,0,0,0,0,0,0,0,110,0,0,0,0,0,0,0,230,0,0,0,0,0,0,0,230,0,0,0,0,0,0,0,231,0,0,0,0,0,1,192,199,0,96,0,0,0,1,192,199,0,112,0,0,0,3,225,199,0,240,0,0,0,3,225,195,0,248,0,0,0,7,225,131,0,248,0,0,0,7,113,131,129,248,0,0,0,14,115,131,129,220,0,0,15,254,51,131,129,156,31,240,15,252,59,131,131,140,63,240,15,252,59,1,131,142,127,240,0,0,31,1,131,142,112,0,0,0,31,1,195,7,224,0,0,0,31,1,199,7,192,0,0,0,14,1,199,7,192,0,0,0,14,1,198,3,128,0,0,0,6,0,206,3,0,0,0,0,0,0,206,0,0,0,0,0,0,0,236,0,0,0,0,0,0,0,252,0,0,0,0,0,0,0,252,0,0,0,0,0,0,0,248,0,0,0,0,0,0,0,120,0,0,0,0,0,0,0,120,0,0,0,0,0,0,0,112,0,0,0,0,0,0,0,112,0,0,0,0,0,0,0,112,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,24,0,0,0,0,0,0,0,28,0,0,0,0,0,0,0,60,0,0,0,0,0,0,0,60,0,0,0,0,0,0,0,60,0,0,0,0,0,0,0,60,0,0,0,0,0,0,0,60,0,0,0,0,0,0,0,126,0,0,0,0,0,0,0,126,0,0,0,0,0,0,0,110,0,0,0,0,0,0,0,110,0,0,0,0,0,0,0,230,0,0,0,0,0,0,0,230,0,0,0,0,0,0,0,231,0,0,0,0,0,1,192,199,0,96,0,0,0,1,192,199,0,112,0,0,0,3,225,199,0,240,0,0,0,3,225,195,0,248,0,0,0,7,225,131,0,248,0,0,0,7,113,131,129,248,0,0,0,14,115,131,129,220,0,0,15,254,51,131,129,156,31,240,15,252,59,131,131,140,63,240,15,252,59,1,131,142,127,240,0,0,31,1,131,142,112,0,0,0,31,1,195,7,224,0,0,0,31,1,199,7,192,0,0,0,14,1,199,7,192,0,0,0,14,1,198,3,128,0,0,0,6,0,206,3,0,0,0,0,0,0,206,0,0,0,0,0,0,0,236,0,0,0,0,0,0,0,252,0,0,0,0,0,0,0,252,0,0,0,0,0,0,0,248,0,0,0,0,0,0,0,120,0,0,0,0,0,0,0,120,0,0,0,0,0,0,0,112,0,0,0,0,0,0,0,112,0,0,0,0,0,0,0,112,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,24,0,0,0,0,0,0,0,28,0,0,0,0,0,0,0,60,0,0,0,0,0,0,0,60,0,0,0,0,0,0,0,60,0,0,0,0,0,0,0,60,0,0,0,0,0,0,0,60,0,0,0,0,0,0,0,126,0,0,0,0,0,0,0,126,0,0,0,0,0,0,0,110,0,0,0,0,0,0,0,110,0,0,0,0,0,0,0,230,0,0,0,0,0,0,0,230,0,0,0,0,0,0,0,231,0,0,0,0,0,1,192,199,0,96,0,0,0,1,192,199,0,112,0,0,0,3,225,199,0,240,0,0,0,3,225,195,0,248,0,0,0,7,225,131,0,248,0,0,0,7,113,131,129,248,0,0,0,14,115,131,129,220,0,0,15,254,51,131,129,156,31,240,15,252,59,131,131,140,63,240,15,252,59,1,131,142,127,240,0,0,31,1,131,142,112,0,0,0,31,1,195,7,224,0,0,0,31,1,199,7,192,0,0,0,14,1,199,7,192,0,0,0,14,1,198,3,128,0,0,0,6,0,206,3,0,0,0,0,0,0,206,0,0,0,0,0,0,0,236,0,0,0,0,0,0,0,252,0,0,0,0,0,0,0,252,0,0,0,0,0,0,0,248,0,0,0,0,0,0,0,120,0,0,0,0,0,0,0,120,0,0,0,0,0,0,0,112,0,0,0,0,0,0,0,112,0,0,0,0,0,0,0,112,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}
};


void setup() {
  Serial.begin(115200);

  Wire.begin(14, 15, 100000); // Substitua pelos pinos SDA e SCL do seu projeto

  if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_I2C_ADDR))
  {
    Serial.println("SSD1306 OLED display failed to initialize.");
    while (true);
  }
}

int frame = 0;
void loop() {
  display.clearDisplay();
  display.drawBitmap(32, 0, frames[frame], 64, 64, 1); // Substitua os valores de largura e altura conforme necessário
  display.display();
  frame = (frame + 1) % FRAME_COUNT;
  delay(FRAME_DELAY);
}

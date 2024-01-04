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
    // Put animation
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


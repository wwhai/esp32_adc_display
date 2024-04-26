#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);
void DrawText(int16_t x, int16_t y, uint8_t size, const char *txt)
{
  display.setTextSize(size);
  display.setTextColor(WHITE);
  display.setCursor(x, y);
  display.print(txt);
  display.display();
}
void setup()
{
  Serial.begin(115200);

  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C))
  {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;)
      ;
  }
  delay(2000);
  display.clearDisplay();
  DrawText(0, 0, 1, "TEMP:");
  DrawText(30, 0, 3, "23.5C");
  DrawText(0, 24, 1, "HUMI:");
  DrawText(30, 24, 3, "78.5%");
  display.display();
}

void loop()
{
}
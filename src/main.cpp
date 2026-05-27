#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SDA_PIN      8
#define SCL_PIN      9
#define SCREEN_W     128
#define SCREEN_H     64
#define OLED_ADDR    0x3C

Adafruit_SSD1306 display(SCREEN_W, SCREEN_H, &Wire, -1);

int    screen     = 0;
unsigned long lastSwitch = 0;
int    barWidth   = 0;
int    scrollX    = SCREEN_W;

void setup() {
  Serial.begin(115200);
  Wire.begin(SDA_PIN, SCL_PIN);

  if (!display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDR)) {
    Serial.println("SSD1306 not found — check wiring!");
    while (true) delay(500);
  }

  display.clearDisplay();
  display.setTextColor(SSD1306_WHITE);
  display.setTextSize(2);
  display.setCursor(14, 12);
  display.print("ESP32-S3");
  display.setTextSize(1);
  display.setCursor(22, 36);
  display.print("OLED test ready");
  display.drawRoundRect(4, 4, 120, 56, 6, SSD1306_WHITE);
  display.display();
  delay(2000);
}

void loop() {
  unsigned long now = millis();

  if (screen != 2 && now - lastSwitch > 2500) {
    screen = (screen + 1) % 4;
    lastSwitch = now;
    scrollX = SCREEN_W;
    barWidth = 0;
  }

  display.clearDisplay();

  switch (screen) {

    case 0:
      display.setTextSize(2);
      display.setCursor(8, 6);
      display.print("Hello,");
      display.setCursor(8, 28);
      display.print("World!");
      display.setTextSize(1);
      display.setCursor(0, 54);
      display.print("ESP32-S3-DevKitC-1");
      display.drawLine(0, 50, 128, 50, SSD1306_WHITE);
      break;

    case 1:
      display.setTextSize(1);
      display.setCursor(0, 0);
      display.print("Shapes");
      display.drawRect(0, 12, 36, 24, SSD1306_WHITE);
      display.fillCircle(64, 24, 14, SSD1306_WHITE);
      display.drawTriangle(92, 36, 110, 10, 128, 36, SSD1306_WHITE);
      display.fillRect(0, 42, 36, 18, SSD1306_WHITE);
      display.drawCircle(64, 50, 10, SSD1306_WHITE);
      display.fillTriangle(92, 60, 110, 38, 128, 60, SSD1306_WHITE);
      break;

    case 2: {
      display.setTextSize(1);
      display.setCursor(0, 0);
      display.print("Loading...");
      display.drawRoundRect(4, 26, 120, 14, 4, SSD1306_WHITE);
      if (barWidth < 116) barWidth += 2;
      display.fillRoundRect(6, 28, barWidth, 10, 3, SSD1306_WHITE);
      int pct = map(barWidth, 0, 116, 0, 100);
      display.setCursor(52, 48);
      display.print(pct);
      display.print("%");
      if (barWidth >= 116 && now - lastSwitch > 600) {
        screen = (screen + 1) % 4;
        lastSwitch = now;
        barWidth = 0;
      }
      break;
    }

    case 3: {
      display.setTextSize(1);
      display.setCursor(0, 0);
      display.print("Marquee scroll:");
      display.drawLine(0, 11, 128, 11, SSD1306_WHITE);
      display.setTextSize(2);
      display.setCursor((int)scrollX, 26);
      display.print("ESP32  SNAKE  GAME ");
      scrollX -= 3;
      if (scrollX < -320) scrollX = SCREEN_W;
      display.setTextSize(1);
      display.setCursor(20, 54);
      display.print("GPIO8=SDA  GPIO9=SCL");
      break;
    }
  }

  display.display();
  delay(30);
}
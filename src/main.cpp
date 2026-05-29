#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SDA_PIN     8
#define SCL_PIN     9
#define JOY_X_PIN   1
#define JOY_Y_PIN   2
#define JOY_SW_PIN  42

#define SCREEN_W    128
#define SCREEN_H    64
#define OLED_ADDR   0x3C
Adafruit_SSD1306 display(SCREEN_W, SCREEN_H, &Wire, -1);

#define BOX_X   74
#define BOX_Y    5
#define BOX_W   50
#define BOX_H   54

void setup() {
  Serial.begin(115200);
  Wire.begin(SDA_PIN, SCL_PIN);
  pinMode(JOY_SW_PIN, INPUT_PULLUP);

  if (!display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDR)) {
    Serial.println("SSD1306 not found!");
    while (true) delay(500);
  }

  display.clearDisplay();
  display.setTextColor(SSD1306_WHITE);
  display.setTextSize(1);
  display.setCursor(14, 20);
  display.print("Joystick + OLED");
  display.setCursor(32, 38);
  display.print("test ready");
  display.display();
  delay(1500);
}

void loop() {
  int rawX = analogRead(JOY_X_PIN);
  int rawY = analogRead(JOY_Y_PIN);
  bool pressed = (digitalRead(JOY_SW_PIN) == LOW);

  int pctX = map(rawX, 0, 4095, 0, 100);
  int pctY = map(rawY, 0, 4095, 0, 100);

  int dotX = map(rawX, 0, 4095, BOX_X + 2, BOX_X + BOX_W - 3);
  int dotY = map(rawY, 0, 4095, BOX_Y + 2, BOX_Y + BOX_H - 3);

  display.clearDisplay();
  display.setTextSize(1);

  display.setCursor(0, 0);
  display.print("X:");
  display.print(rawX);

  display.setCursor(0, 12);
  display.print("Y:");
  display.print(rawY);

  display.setCursor(0, 24);
  display.print("X%:");
  display.print(pctX);

  display.setCursor(0, 36);
  display.print("Y%:");
  display.print(pctY);

  if (pressed) {
    display.setCursor(0, 52);
    display.print("PRESSED");
  }

  display.drawLine(70, 0, 70, 63, SSD1306_WHITE);
  display.drawRect(BOX_X, BOX_Y, BOX_W, BOX_H, SSD1306_WHITE);

  int midX = BOX_X + BOX_W / 2;
  int midY = BOX_Y + BOX_H / 2;
  display.drawLine(midX, BOX_Y + 1, midX, BOX_Y + BOX_H - 2, SSD1306_WHITE);
  display.drawLine(BOX_X + 1, midY, BOX_X + BOX_W - 2, midY, SSD1306_WHITE);

  display.fillRect(dotX - 1, dotY - 1, 3, 3, SSD1306_WHITE);

  if (pressed) {
    display.fillRect(BOX_X + 1, BOX_Y + 1, 14, 9, SSD1306_WHITE);
    display.setTextColor(SSD1306_BLACK);
    display.setCursor(BOX_X + 2, BOX_Y + 2);
    display.print("BTN");
    display.setTextColor(SSD1306_WHITE);
  }

  display.display();

  Serial.print("X="); Serial.print(rawX);
  Serial.print("  Y="); Serial.print(rawY);
  Serial.print("  SW="); Serial.println(pressed ? "PRESSED" : "open");

  delay(30);
}
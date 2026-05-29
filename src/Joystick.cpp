#include "Joystick.h"

//constructor
Joystick::Joystick(int xPin, int yPin, int swPin, int center, int threshold)
    : xPin(xPin), yPin(yPin), swPin(swPin), center(center), threshold(threshold) {}

void Joystick::begin() {
    pinMode(swPin, INPUT_PULLUP);
}

Position Joystick::get_direction() {
  int x = analogRead(xPin) - JOY_CENTER;
  int y = analogRead(yPin) - JOY_CENTER;

  if (abs(x) < JOY_THRESH && abs(y) < JOY_THRESH) return Position(0, 0);

  if (abs(x) > abs(y)) {
    return (x > 0) ? Position(1, 0) : Position(-1, 0);
  } else {
    return (y > 0) ? Position(0, -1) : Position(0, 1);
  }
}

bool Joystick::is_pressed() {
  return digitalRead(swPin) == LOW;
}

int Joystick::get_raw_x() {
    return xPin;
}

int Joystick::get_raw_y() {
    return yPin;
}

Position Joystick::get_raw_position() {
    return Position(xPin, yPin);
}
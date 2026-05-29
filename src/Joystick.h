#ifndef JOYSTICK_H
#define JOYSTICK_H

#include <Arduino.h>   // analogRead(), digitalRead(), pinMode(), map()
#include "Position.h"

#define JOY_CENTER  2048
#define JOY_THRESH  600   // must exceed this distance from centre to register

/**
 * enum is a way to define a named set of constants — instead of using meaningless
 * numbers like 0, 1, 2 to represent states or directions, you give them readable names
 * like UP, DOWN, LEFT, RIGHT, and the compiler automatically assigns the numbers behind
 * the scenes. It makes code much easier to read and works especially well with switch
 * statements
 */
//enum Direction { CENTRE, UP, DOWN, LEFT, RIGHT };


/* Def of each direction:
    ┌─────────────────────────────┐
    │         UP (Y < 1448)       │
    ├────────┬────────┬───────────┤
    │        │ CENTRE │           │
LEFT│ X<1448 │  zone  │ X>2648    │RIGHT
    │        │        │           │
    ├────────┴────────┴───────────┤
    │        DOWN (Y > 2648)      │
    └─────────────────────────────┘
*/

class Joystick {
    private:
        int xPin;
        int yPin;
        int swPin;
        int center;
        int threshold;

    public:
        Joystick(int xPin, int yPin, int swPin, int center = JOY_CENTER, int threshold = JOY_THRESH);

        void begin();   // call in setup() — sets pinMode
        Position get_direction();
        bool is_pressed();
        int get_raw_x();
        int get_raw_y();
        Position get_raw_position();

};

#endif
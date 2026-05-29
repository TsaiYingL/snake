#ifndef POSITION_H
#define POSITION_H

#include <iostream>
#include <ostream>

struct Position {
    int x, y;

    //initialize new position
    Position(int x_pos, int y_pos) : x(x_pos), y(y_pos) {}

    // compare two positions
    //a == b is the same as a.operator==(b)
    bool operator==(const Position& other) const {
        return x == other.x && y == other.y;
    }

    friend std::ostream& operator<<(std::ostream& os, const Position& pos) {
        os << "(" << pos.x << ", " << pos.y << ")";
        return os;
    }
};

#endif
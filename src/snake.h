#ifndef SNAKE_H
#define SNAKE_H

#include "DoublyLinkedList.h"
#include "Position.h"
#include "Node.h"

class Snake {
    private:
        /**
         * set up for the snake:
         * body: a ddl that stores all position that is being taken up for the snake
         * points: keep track of the points
         */
        DoublyLinkedList<Position> body;
        int points;

    public:
        Snake();
        Snake(Position p);
        Snake(int x, int y);
        ~Snake();

        //movement
        void move(Position direction);
        void grow(int dx, int dy);

        //getters
        Position get_head()   const;
        Position get_tail()   const;
        int      get_size()   const;
        int      get_points() const;

        //game logic
        void add_points(int amount);
        bool alive()        const;
        bool hit_self()       const;

        void clear();

};

#endif
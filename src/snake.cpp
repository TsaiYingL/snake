#include "snake.h"

//constructor / destructor
Snake::Snake() : body(Position(0,0)), points(0) {}

Snake::Snake(Position p) : body(p), points(0) {}

Snake::Snake(int x, int y) : body(Position(x,y)), points(0) {}

Snake::~Snake() { clear(); }

// movement
void Snake::move(int dx, int dy) {
    Position curr = body.get_head()->data;
    body.push_front(Position(curr.x + dx, curr.y + dy));
    body.pop_back();
}

void Snake::grow(int dx, int dy) {
    Position curr = body.get_head()->data;
    body.push_front(Position(curr.x + dx, curr.y + dy));
}

// getters
Position Snake::get_head() const{
    return body.get_head()->data;
}

Position Snake::get_tail() const{
    return body.get_tail()->data;
}

int Snake::get_size() const {
    return body.get_size();
}

int Snake::get_points() const {
    return points;
}

//game logic
void Snake::add_points(int amount) {
    points += amount;
}

bool Snake::hit_self() const {
    Position head = body.get_head() -> data;

    Node<Position>* temp = body.get_head() -> next;

    while(temp) {
        if (temp->data == head) {
            return true;
        }
        temp = temp->next;
    }

    return false;
}

bool Snake::is_alive() const {
    return !hit_self();
}

//clear
void Snake::clear() {
    body.clear();
    //points allocated the stack, not the heap, thus no need to delete
    points = 0;
}
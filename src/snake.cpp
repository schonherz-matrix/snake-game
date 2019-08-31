#include "snake.h"
#include <stdexcept>

Snake::Snake(QColor color) :
    color(color) {}

void Snake::init(int x, int y, unsigned length) {
    if (y < length) {
        throw std::invalid_argument("Length must be less or equal to y.");
    }

    for (unsigned i = 0; i < length; i++) {
        QPoint point(x, y-i);
        this->body.push_back(point);
    }
}

bool Snake::collides(int x, int y) {
    for (unsigned i = 0; i < body.size(); i++) {
        if (body[i].x() == x && body[i].y() == y) return true;
    }
    return false;
}

void Snake::setBiteCoords(int x, int y) {
    // TODO
}


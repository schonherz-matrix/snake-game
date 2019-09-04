#include "snake.h"
#include "config.h"
#include <stdexcept>
#include <QPainter>

Snake::Snake(QColor color) :
    color(color) {}

/**
* Initializes the head of the snake in the given points, below parts pointing down.
* Then length can also be given.
*/
void Snake::init(int x, int y, unsigned length) {
    if (y < length) {
        throw std::invalid_argument("Length must be less or equal to y.");
    }

    for (unsigned i = 0; i < length; i++) {
        QPoint point(x, y-i);
        this->body.push_back(point);
    }
}

/**
* Clears the points of the snake.
*/
void Snake::clean() {
    body.clear();
}

/**
* Moves the snake. If it collides with itself, then emits a signal indicating game over.
* If it hits a bite, then it eats it.
*
* @param dir: the direction to move into
* @return true, if the snake hit a bite.
*/
bool Snake::move(Direction dir) {
    switch (dir) {
        case Direction::UP:
            // if snake is already on the top
            if (body[0].y() == 0) {
                return advance(body[0].x(), config::dimension::height);
            } else {
                return advance(body[0].x(), body[0].y()-1);
            }

        case Direction::DOWN:
            // if snake is already on the bottom
            if (body[0].y() == config::dimension::height) {
                return advance(body[0].x(), 0);
            } else {
                return advance(body[0].x(), body[0].y()+1);
            }

        case Direction::LEFT:
            // if snake is already on the left
            if (body[0].x() == 0) {
                return advance(config::dimension::width, body[0].y());
            } else {
                return advance(body[0].x()-1, body[0].y());
            }

        case Direction::RIGHT:
            // if snake is already on the right
            if (body[0].x() == config::dimension::width) {
                return advance(0, body[0].y());
            } else {
                return advance(body[0].x()+1, body[0].y());
            }
    }

    // should never reach this point
    return false;
}

/**
* Checks if the given point collides with any point of the snake.
*
* @param x: the x coordinate of the given point
* @param y: the y coordinate of the given point
* @return true, if the given point does collide.
*/
bool Snake::collides(int x, int y) {
    for (unsigned i = 0; i < body.size(); i++) {
        if (body[i].x() == x && body[i].y() == y) return true;
    }
    return false;
}

/**
* Sets the coordinates of the bite
*
* @param x: the x coordinate of the bite
* @param y: the y coordinate of the bite
*/
void Snake::setBiteCoords(int x, int y) {
    this->biteX = x;
    this->biteY = y;
}

/**
* Returns the length of the snake.
*/
int Snake::getLength() {
    return body.size();
}

/**
* Tries to advance to the new position. If it collides with itself, then emits a signal
* indicating game over. If it hits a bite, then it eats it.
*
* @param x: the new x position of the snake
* @param y: the new y position of the snake
* @return true, if the snake hit a bite.
*/
bool Snake::advance(int x, int y) {
    if (this->collides(x, y)) {
        emit hitMyself();
        return false;
    } else {
        if (biteX == x && biteY == y) {
            body.push_front(QPoint(x, y));
            return true;
        } else {
            body.push_front(QPoint(x, y));
            body.pop_back();
            return false;
        }
    }
}

/**
* Paints each point of the snake.
*/
void Snake::paint(QPainter *painter) {
    painter->setPen(QPen(color, 1));
    for (int i = 0; i < body.size(); i++) {
        painter->drawPoint(body[i].x(), body[i].y());
    }
}

#include "bite.h"
#include "config.h"
#include <QRandomGenerator>
#include <QPainter>

/**
* Constructor of Bite: sets it's color.
*
* @param color: the color of the bite
*/
Bite::Bite(QColor color) :
    color(color) {}

/**
* Regenerates the bite on the board. Searches for a place that's not the same as before,
* then checks if it collides with the snake. In this case, it tries the place right, checks
* collision, etc. If it reaches the right side of the board, then tries the row below,
* on the left side of the board. If it reaches the end, then it starts again from the top left
* corner.
*
* @param snake: the snake of the board
*/
void Bite::regenerate(Snake &snake) {
    int newX;
    do {
        newX = QRandomGenerator::global()->bounded(0, (config::dimension::width/2))*2 + 1;
    } while (newX == this->x());

    int newY;
    do {
        newY = QRandomGenerator::global()->bounded(0, (config::dimension::height/2))*2 + 1;
    } while (newY == this->y());

    while (snake.collides(newX, newY)
           || snake.collides(newX, newY)
           || snake.collides(newX, newY)
           || snake.collides(newX, newY)) {

        if (newX == config::dimension::width-1) {
            newX = 1;
            if (newY == config::dimension::height-1) {
                newY = 1;
            } else {
                newY++;
                newY++;
            }
        } else {
            newX++;
            newX++;
        }
    }

    this->_x = newX;
    this->_y = newY;
}

/**
* Checks if snake collided with bite or not.
*
* @param x: the x coordinate of the snake's head
* @param y: the y coordinate of the snake's head
*/
bool Bite::collide(int x, int y) {
    return (x == this->_x || x == this->_x-1) && (y == this->_y || y == this->_y-1);
}

/**
* Paints the bite.
*
* @param painter: the painter to paint on
*/
void Bite::paint(QPainter *painter) {
    painter->setPen(QPen(color, 1));
    painter->drawPoint(this->_x, this->_y);
    painter->drawPoint(this->_x, this->_y-1);
    painter->drawPoint(this->_x-1, this->_y);
    painter->drawPoint(this->_x-1, this->_y-1);

}

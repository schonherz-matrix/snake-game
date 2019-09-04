#include "bite.h"
#include "config.h"
#include <QRandomGenerator>

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
    int newX = this->x();
    do {
        newX = QRandomGenerator::system()->bounded(config::dimension::width);
    } while (newX == this->x());

    int newY = this->y();
    do {
        newY = QRandomGenerator::system()->bounded(config::dimension::height);
    } while (newY == this->y());

    while (snake.collides(newX, newY)) {
        if (newX == config::dimension::width) {
            newX = 0;
            if (newY == config::dimension::height) {
                newY = 0;
            } else {
                newY++;
            }
        } else {
            newX++;
        }
    }
}

#include "bite.h"
#include "config.h"
#include <QRandomGenerator>

Bite::Bite(QColor color) :
    color(color) {}

void Bite::regenerate(Snake snake) {
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


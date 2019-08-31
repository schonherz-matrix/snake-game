#ifndef SNAKE_H
#define SNAKE_H

#include <vector>
#include <QPoint>
#include <QColor>
#include "direction.h"

class Snake {
private:
    std::vector<QPoint> body;
    QColor color;
    int biteX, biteY;

public:
    Snake(QColor color);
    void init(int x, int y, unsigned length);

    bool move(Direction dir);
    bool collides(int x, int y);
    void setBiteCoords(int x, int y);
};

#endif // SNAKE_H

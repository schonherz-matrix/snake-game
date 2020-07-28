#ifndef BITE_H
#define BITE_H

#include <QPoint>
#include <QColor>
#include "snake.h"

class Snake;

class Bite {
private:
    // Coordinates of the bite:
    // (x-1, y-1) (x, y-1)
    // (x, y-1)   (x, y)

    int _x;
    int _y;

public:
    QColor color;
    int x() { return _x; }
    int y() { return _y; }

    Bite(QColor);
    void regenerate(Snake &snake);
    bool collide(int x, int y);
    void paint(QPainter *painter);
};

#endif // BITE_H

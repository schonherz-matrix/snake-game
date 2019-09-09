#ifndef BITE_H
#define BITE_H

#include <QPoint>
#include <QColor>
#include "snake.h"

class Snake;

class Bite {
private:
    int _x;
    int _y;

public:
    QColor color;
    int x() { return _x; }
    int y() { return _y; }

    Bite(QColor);
    void regenerate(Snake &snake);
};

#endif // BITE_H

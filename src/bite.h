#ifndef BITE_H
#define BITE_H

#include <QPoint>
#include <QColor>
#include "snake.h"

class Snake;

class Bite : public QPoint {
public:
    QColor color;

    Bite(QColor);
    void regenerate(Snake &snake);
};

#endif // BITE_H

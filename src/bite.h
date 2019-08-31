#ifndef BITE_H
#define BITE_H

#include <QPoint>
#include <QColor>
#include "snake.h"

class Bite : public QPoint {
private:
    QColor color;

public:
    Bite(QColor);
    void regenerate(Snake snake);
};

#endif // BITE_H

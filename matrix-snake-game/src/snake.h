#ifndef SNAKE_H
#define SNAKE_H

#include <deque>
#include <QPoint>
#include <QColor>
#include <QGraphicsObject>
#include "direction.h"

class Bite;

class Snake : public QObject{
    Q_OBJECT

private:
    std::deque<QPoint> body;
    QColor color;
    Bite* bite;

signals:
    void hitMyself();

public:
    Snake(QColor color);
    void init(int x, int y, unsigned length);
    void clean();

    bool move(Direction dir);
    bool collides(int x, int y);
    void setBite(Bite* bite);
    int getLength();
    bool advance(int x, int y);

    void paint(QPainter *painter);

    virtual ~Snake() {}
};

#endif // SNAKE_H

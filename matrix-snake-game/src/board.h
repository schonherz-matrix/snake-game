#ifndef BOARD_H
#define BOARD_H

#include <QGraphicsObject>
#include "snake.h"
#include "bite.h"

class Board : public QGraphicsObject {
    Q_OBJECT

private:
    Snake snake;
    Bite bite;

signals:
    void finished();

public slots:
    void snakeHitItself();

public:
    Board();

    void init();
    void move(Direction dir);
    void restart();
    bool isWin();

    QRectF boundingRect() const override;
    QPainterPath shape() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

};

#endif // BOARD_H

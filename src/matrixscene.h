#ifndef MATRIXSCENE_H
#define MATRIXSCENE_H

#include <common/frame.h>
#include <muebtransmitter.h>
#include <QGraphicsScene>
#include <QImage>
#include <QObject>
#include <QPainter>
#include <QTimer>
#include <QList>
#include "snake.h"
#include "bite.h"

class MatrixScene : public QGraphicsScene {
  Q_OBJECT

public:
    MatrixScene(QObject *parent = nullptr);

private:
    Frame out;
    QImage frame;
    QPainter painter;
    MUEBTransmitter transmitter;
    int timerID;

    Snake snake;
    Bite bite;

  // QObject interface
protected:
    void timerEvent(QTimerEvent *event) override;
};

#endif // MATRIXSCENE_H

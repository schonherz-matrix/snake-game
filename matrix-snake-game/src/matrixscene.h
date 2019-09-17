#ifndef MATRIXSCENE_H
#define MATRIXSCENE_H

#include <muebtransmitter.h>
#include <QGraphicsScene>
#include <QImage>
#include <QObject>
#include <QPainter>
#include <QTimer>
#include <QList>
#include <QNetworkAccessManager>
#include "board.h"
#include <QSlider>


class MatrixScene : public QGraphicsScene {
  Q_OBJECT

public:
    MatrixScene(QObject *parent = nullptr);
    void setSlider(QSlider* slider);

public slots:
    void endGame();
    void makeMove(QNetworkReply *reply);
    void resetTimerInterval(int time);
    void timerTick();

private:
    QImage frame;
    QPainter painter;
    MUEBTransmitter transmitter;
    QNetworkAccessManager manager;
    QTimer timer;
    bool gameOver = false;

    Board board;
    QSlider* slider;
};

#endif // MATRIXSCENE_H

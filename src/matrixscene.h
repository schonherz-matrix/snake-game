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
#include <QNetworkAccessManager>
#include "board.h"


class MatrixScene : public QGraphicsScene {
  Q_OBJECT

public:
    MatrixScene(QObject *parent = nullptr);

public slots:
    void endGame();
    void makeMove(QNetworkReply *reply);

private:
    Frame out;
    QImage frame;
    QPainter painter;
    MUEBTransmitter transmitter;
    QNetworkAccessManager manager;
    int timerID;
    bool gameOver = false;

    Board board;

  // QObject interface
protected:
    void timerEvent(QTimerEvent *event) override;
};

#endif // MATRIXSCENE_H

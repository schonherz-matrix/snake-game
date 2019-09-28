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
#include <QCheckBox>
#include "board.h"
#include <QSlider>
#include <SFML/Audio.hpp>


class MatrixScene : public QGraphicsScene {
  Q_OBJECT

public:
    MatrixScene(QObject *parent = nullptr);
    void setSlider(QSlider* speedSlider);
    void setGrowthSwitch(QCheckBox* button);

public slots:
    void endGame();
    void makeMove(QNetworkReply *reply);
    void resetTimerInterval(int time);
    void timerTick();
    void playBiteSound();

private:
    QImage frame;
    QPainter painter;
    MUEBTransmitter transmitter;
    QNetworkAccessManager manager;
    QTimer timer;
    bool gameOver = false;
    Direction currentDir;
    sf::SoundBuffer soundBuffer;
    sf::Sound biteSound;

    Board board;
    QSlider* speedSlider;
    QCheckBox* growthButton;

    Direction oppositeDir(Direction);
};

#endif // MATRIXSCENE_H

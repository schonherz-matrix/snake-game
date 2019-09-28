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
#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <QSlider>
#include <QSoundEffect>


class MatrixScene : public QGraphicsScene {
  Q_OBJECT

public:
    MatrixScene(QObject *parent = nullptr);
    void setSlider(QSlider* speedSlider);
    void setGrowthSwitch(QCheckBox* button);
    void setMusicSwitch(QCheckBox* button);
    void setSFXSwitch(QCheckBox* button);

public slots:
    void endGame();
    void makeMove(QNetworkReply *reply);
    void resetTimerInterval(int time);
    void timerTick();
    void playBiteSound();
    void stopMusic();
    void switchPauseMusic(int state);

private:
    QImage frame;
    QPainter painter;
    MUEBTransmitter transmitter;
    QNetworkAccessManager manager;
    QTimer timer;
    bool gameOver = false;
    Direction currentDir;

    QSoundEffect biteSound;
    QMediaPlaylist playlist;
    QMediaPlayer music;
    int musicVolume;

    Board board;
    QSlider* speedSlider;
    QCheckBox* growthButton;
    QCheckBox* musicButton;
    QCheckBox* sfxButton;

    Direction oppositeDir(Direction);
};

#endif // MATRIXSCENE_H

#include "matrixscene.h"
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QRandomGenerator>
#include <QJsonDocument>
#include <QJsonObject>
#include <QVariantMap>
#include <QNetworkReply>
#include <QGraphicsPixmapItem>
#include "config.h"
#include "direction.h"
#include <SFML/Audio.hpp>


MatrixScene::MatrixScene(QObject *parent)
    : QGraphicsScene(parent),
      frame(config::dimension::width,
            config::dimension::height,
            QImage::Format_RGB888),
      painter(&frame),
      timer(),
      soundBuffer(),
      biteSound()
{

    // set BG
    setBackgroundBrush(Qt::black);

    // setSize
    setSceneRect(0, 0, config::dimension::width, config::dimension::height);

    // init Timer
    timer.start(config::game::query);
    connect(&timer, &QTimer::timeout, this, &MatrixScene::timerTick);

    // init Map
    board.setPos(0,0);
    board.init();
    this->currentDir = Direction::UP;
    addItem(&board);

    connect(&board, &Board::finished, this, &MatrixScene::endGame);

    // init networking
    connect(&manager, &QNetworkAccessManager::finished,
            this, &MatrixScene::makeMove);

    render(&painter);
    transmitter.sendFrame(frame);

    // init sound
    if (soundBuffer.loadFromFile("resources/bite.wav")) {
        qDebug() << "Sound loaded successfully!\n";
    } else {
        qDebug() << "Could not load sound!\n";
    }
    biteSound.setBuffer(soundBuffer);
    connect(&board, &Board::biteTaken, this, &MatrixScene::playBiteSound);
}

/**
* Ends the game: kills the timer, prints out a big "Game over" sign
*/
void MatrixScene::endGame() {
    qDebug() << "Ending game...\n";

    gameOver = true;
    timer.stop();
    qDebug() << "Timer killed.\n";

    QPixmap pix;
    if (board.isWin()) {
        if(pix.load(":/images/win.png")){
            addPixmap(pix);
            qDebug() << "Pixmap added.\n";
            render(&painter);
            transmitter.sendFrame(frame);
            qDebug() << "Now you should see it on the emulator.\n";

        } else {
            qDebug() << "Error while loading pixmap!";
        }
    } else {
        if(pix.load(":/images/gameover.png")){
            addPixmap(pix);
            qDebug() << "Pixmap added.\n";
            render(&painter);
            transmitter.sendFrame(frame);
            qDebug() << "Now you should see it on the emulator.\n";

        } else {
            qDebug() << "Error while loading pixmap!";
        }
    }
}

/**
* On reply, the MatrixScene makes the move (only if the reply isn't an error).
*
* @param reply: the reply from the backend
*/
void MatrixScene::makeMove(QNetworkReply *reply) {
    // Get the direction from the answer
    if (reply->error()) {
        qDebug() << "Error occured in request:\n";
        qDebug() << reply->errorString() << "\n";
        return;
    }

    QJsonDocument doc = QJsonDocument::fromJson(reply->readAll());
    QJsonObject jObject = doc.object();
    qDebug() << jObject << "\n";

    QVariantMap mainMap = jObject.toVariantMap();
    QVariantMap dataMap = mainMap["directions"].toMap();

    std::map<Direction, int> directions;
    std::map<Direction, int>::iterator it = directions.begin();

    directions.insert(it, std::pair<Direction, int>(Direction::UP, dataMap["up"].toInt()));
    directions.insert(it, std::pair<Direction, int>(Direction::DOWN, dataMap["down"].toInt()));
    directions.insert(it, std::pair<Direction, int>(Direction::LEFT, dataMap["left"].toInt()));
    directions.insert(it, std::pair<Direction, int>(Direction::RIGHT, dataMap["right"].toInt()));

    qDebug() << "Votes: \nUp: " << directions[Direction::UP]
             << "\nDown: " << directions[Direction::DOWN]
             << "\nLeft: " << directions[Direction::LEFT]
             << "\nRight: " << directions[Direction::RIGHT] << "\n";

    int maxVotes = 0;
    for (int i = 0; i < 4; i++) {
        if (Direction(i) == oppositeDir(currentDir)) {
            qDebug() << "Direction " << i << " skipped." << "\n";
            continue;
        }
        if (directions[Direction(i)] > maxVotes) {
            maxVotes = directions[Direction(i)];
        }
    }

    qDebug() << "Maximum votes: " << maxVotes << "\n";

    std::vector<Direction> equalDirs;

    for (int i = 0; i < 4; i++) {
        if (Direction(i) == oppositeDir(currentDir)) {
            continue;
        }
        if (directions[Direction(i)] == maxVotes) equalDirs.push_back(Direction(i));
    }

    qDebug() << "Directions with this number of votes:\n";
    for (int i = 0; i < equalDirs.size(); i++) {
        switch (equalDirs[i]) {
        case Direction::LEFT:
            qDebug() << "LEFT" << "\n";
            break;
        case Direction::UP:
            qDebug() << "UP" << "\n";
            break;
        case Direction::DOWN:
            qDebug() << "DOWN" << "\n";
            break;
        case Direction::RIGHT:
            qDebug() << "RIGHT" << "\n";
            break;
        }
    }

    int newDirIndex = 0;
    if (equalDirs.size() > 1) {
        newDirIndex = QRandomGenerator::global()->bounded(0, equalDirs.size());
    }

    Direction newDir = equalDirs[newDirIndex];

    if (newDir == Direction::UP) {
        qDebug() << "New direction: UP\n";
    } else if (newDir == Direction::DOWN) {
        qDebug() << "New direction: DOWN\n";
    } else if (newDir == Direction::LEFT) {
        qDebug() << "New direction: LEFT\n";
    } else {
        qDebug() << "New direction: RIGHT\n";
    }

    // Move
    board.move(newDir);
    this->currentDir = newDir;

    render(&painter);
    transmitter.sendFrame(frame);
}

/**
* Resets the timer's interval to the new given value.
* 0 = 0 ms
* 20 = 800 ms
* 40 = 1600 ms
*/
void MatrixScene::resetTimerInterval(int time) {
    timer.setInterval(1600-time*40);
}

/**
* Sets the slider of the window.
*
* @param slider
*/
void MatrixScene::setSlider(QSlider *slider) {
    this->slider = slider;
    connect(slider, &QSlider::valueChanged, this, &MatrixScene::resetTimerInterval);
}

/**
* Plays bite sound.
*/
void MatrixScene::playBiteSound() {
    biteSound.setBuffer(soundBuffer);
    biteSound.play();
}

/**
* Main event loop. On every tick, if it's not game over yet,
* it creates a GET request to the backend to find out the next direction.
*/
void MatrixScene::timerTick() {
    if (!gameOver) {
        QNetworkRequest request(config::game::url);
        manager.get(request);
    }
}

/**
* Returns the opposite direction of the given direction.
*/
Direction MatrixScene::oppositeDir(Direction dir) {
    switch (dir) {
        case Direction::UP: return Direction::DOWN;
        case Direction::DOWN: return Direction::UP;
        case Direction::LEFT: return Direction::RIGHT;
        case Direction::RIGHT: return Direction::LEFT;
    }
}

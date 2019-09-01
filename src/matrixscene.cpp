#include "matrixscene.h"
#include <iostream>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QRandomGenerator>
#include <QJsonDocument>
#include <QJsonObject>
#include <QVariantMap>
#include <QNetworkReply>
#include "config.h"

MatrixScene::MatrixScene(QObject *parent)
    : QGraphicsScene(parent),
      frame(config::dimension::width,
            config::dimension::height,
            QImage::Format_RGB888),
      painter(&frame)
{

    // set BG
    setBackgroundBrush(Qt::black);

    // setSize
    setSceneRect(0, 0, config::dimension::width, config::dimension::height);

    // init Timer
    timerID = startTimer(config::game::query);

    // init Map
    board.setPos(0,0);
    board.init();
    addItem(&board);

    connect(&board, &Board::finished, this, &MatrixScene::endGame);

    // init networking
    connect(&manager, &QNetworkAccessManager::finished,
            this, &MatrixScene::makeMove);
}

/**
* Ends the game: kills the timer, prints out a big "Game over" sign
*/
void MatrixScene::endGame() {
    gameOver = true;
    killTimer(timerID);
    addRect(0, 0, 32, 26, Qt::NoPen, Qt::black);

    QFont font("Times", 10, QFont::Bold);

    QGraphicsTextItem* text = new QGraphicsTextItem();
    text->setPos(2, 5);
    text->setFont(font);
    text->setPlainText("Game over");

    addItem(text);

    render(&painter);
    transmitter.sendFrame(frame);
}

/**
* On reply, the MatrixScene makes the move (only if the reply isn't an error).
*
* @param reply: the reply from the backend
*/
void MatrixScene::makeMove(QNetworkReply *reply) {
    // Get the direction from the answer
    Direction dir = Direction::UP;

    if (reply->error()) {
        qDebug() << "Error occured in request\n";
        return;
    }

    QJsonDocument doc = QJsonDocument::fromJson(reply->readAll());
    QJsonObject jObject = doc.object();
    QVariantMap mainMap = jObject.toVariantMap();
    QVariantMap dataMap = mainMap["directions"].toMap();

    int upVotes = dataMap["up"].toInt();
    int downVotes = dataMap["down"].toInt();
    int leftVotes = dataMap["left"].toInt();
    int rightVotes = dataMap["right"].toInt();

    if (upVotes >= downVotes
            && upVotes >= leftVotes
            && upVotes >= rightVotes) {

        dir = Direction::UP;
        qDebug() << "New direction: UP\n";

    } else if (downVotes >= upVotes
               && downVotes >= leftVotes
               && downVotes >= rightVotes) {

        dir = Direction::DOWN;
        qDebug() << "New direction: DOWN\n";

    } else if (leftVotes >= upVotes
               && leftVotes >= downVotes
               && leftVotes >= rightVotes) {

        dir = Direction::LEFT;
        qDebug() << "New direction: LEFT\n";

    } else {

        dir = Direction::RIGHT;
        qDebug() << "New direction: RIGHT\n";
    }

    // Move
    board.move(dir);

    render(&painter);
    transmitter.sendFrame(frame);
}


/**
* Main event loop. On every tick, if it's not game over yet,
* it creates a GET request to the backend to find out the next direction.
*/
void MatrixScene::timerEvent(QTimerEvent *event) {
    Q_UNUSED(event)

    if (!gameOver) {
        QNetworkRequest request(config::game::url);
        manager.get(request);
    }
}

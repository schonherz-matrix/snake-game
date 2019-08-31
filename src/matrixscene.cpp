#include "matrixscene.h"
#include <QRandomGenerator>
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

    // init Frame
    out.pixels = Array2D<Color>(config::dimension::width, config::dimension::height);
    frame.fill(Qt::black);
    for (size_t x = 0; x < out.pixels.getWidth(); x++) {
        for (size_t y = 0; y < out.pixels.getHeight(); y++) {
          out.pixels(x, y) = Color(0, 0, 0);
        }
    }
    transmitter.sendFrame(out);

    // init Timer
    timerID = startTimer(config::game::query);

    // init Map
    board.setPos(0,0);
    board.init();
    addItem(&board);

    connect(&board, &Board::finished, this, &MatrixScene::endGame);
}

void MatrixScene::endGame() {
    gameOver = true;
    killTimer(timerID);
    addRect(0, 0, 32, 26, Qt::NoPen, Qt::black);
    auto text = addText("Game over", QFont("Times", 10, QFont::Bold));
    text->setPos(2, -5);
}


// Main event loop
void MatrixScene::timerEvent(QTimerEvent *event) {
    Q_UNUSED(event)

    if (!gameOver) {
        // TODO!!: ask server where to go
        Direction dir(Direction::UP);

        // Move
        board.move(dir);
    }

    render(&painter);
    transmitter.sendFrame(out);
}

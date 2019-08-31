#include "matrixscene.h"
#include <QRandomGenerator>
#include "config.h"

MatrixScene::MatrixScene(QObject *parent)
    : QGraphicsScene(parent),
      frame(config::dimension::width,
            config::dimension::height,
            QImage::Format_RGB888),
      painter(&frame),
      snake(Qt::green),
      bite(Qt::red)
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
    timerID = startTimer(config::gameSpeed::query);

    // init Map
    snake.init(config::dimension::width / 2,
               config::dimension::height / 2,
               3);
    bite.regenerate(snake);
    snake.setBiteCoords(bite.x(), bite.y());
}

// Main event loop
void MatrixScene::timerEvent(QTimerEvent *event) {
    Q_UNUSED(event)

    // TODO!!: ask server where to go
    Direction dir(Direction::UP);

    // Move
    bool regenerateBite = snake.move(dir);
    if (regenerateBite) {
        bite.regenerate(snake);
        snake.setBiteCoords(bite.x(), bite.y());
    }

    render(&painter);
    for (size_t x = 0; x < out.pixels.getWidth(); x++) {
      for (size_t y = 0; y < out.pixels.getHeight(); y++) {
        auto pixel = frame.pixelColor(static_cast<int>(x), static_cast<int>(y));
        out.pixels(x, y) = Color( static_cast<uint8_t>(pixel.red()),
                                  static_cast<uint8_t>(pixel.green()),
                                  static_cast<uint8_t>(pixel.blue())
                                  );
      }
    }
    transmitter.sendFrame(out);
}

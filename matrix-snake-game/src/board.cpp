#include "board.h"
#include "config.h"
#include <QPainter>

/**
* Constructor of the board.
* Creates the snake with the given color, and also the bite.
*/
Board::Board() :
    snake(config::color::snakeColor),
    bite(config::color::biteColor) {}

/**
* Initializes the snake on the middle of the board with 3 as the length,
* and generates a bite.
*/
void Board::init() {
    snake.init(config::dimension::width / 2,
               config::dimension::height / 2,
               3);
    bite.regenerate(snake);
    snake.setBite(&bite);
    connect(&snake, &Snake::hitMyself, this, &Board::snakeHitItself);
}

/**
* Makes the snake move in the given direction. Regenerates the bite if needed,
* and if the max length is reached, emits a finished signal.
*
* @param dir: the direction to move into
*/
void Board::move(Direction dir) {
    bool regenerateBite = snake.move(dir);
    if (regenerateBite) {
        if (snake.getLength() == config::game::maxLength) {
            emit finished();
        } else {
            bite.regenerate(snake);
        }
    }
}

/**
* Restarts the game.
*/
void Board::restart() {
    snake.clean();
    snake.init(config::dimension::width / 2,
               config::dimension::height / 2,
               3);
    bite.regenerate(snake);
}

/**
* Returns if game is a win, which means the snake got to it's maximum length
*/
bool Board::isWin() {
    return snake.getLength() == config::game::maxLength;
}

/**
* The board got a signal that the snake hit itself, so the game is over.
*/
void Board::snakeHitItself() {
    emit finished();
}

/** Drawing functions */

QRectF Board::boundingRect() const {
    return QRect(0, 0, config::dimension::width, config::dimension::height);
}

QPainterPath Board::shape() const {
    QPainterPath path;
    path.addRect(0, 0, config::dimension::width, config::dimension::height);
    return path;
}

void Board::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    Q_UNUSED(option)
    Q_UNUSED(widget)

    bite.paint(painter);
    snake.paint(painter);
}

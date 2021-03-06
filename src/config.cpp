#include "config.h"

using namespace config;

const tick config::game::query = 800;
const int config::game::maxLength = 20;
const QUrl config::game::url("https://matrix-snake.sch.bme.hu/status");

int config::dimension::width = 32;
int config::dimension::height = 26;

QColor config::color::snakeBodyColor = Qt::green;
QColor config::color::snakeHeadColor = Qt::white;
QColor config::color::biteColor = Qt::red;

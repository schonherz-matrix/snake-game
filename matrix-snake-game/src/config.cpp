#include "config.h"

using namespace config;

const tick config::game::query = 800;
const int config::game::maxLength = 40;
const QUrl config::game::url("https://matrix-snake.sch.bme.hu/status");

int config::dimension::width = 32;
int config::dimension::height = 26;

QColor config::color::snakeColor = Qt::green;
QColor config::color::biteColor = Qt::red;

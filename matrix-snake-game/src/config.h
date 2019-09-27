#ifndef CONFIG_H
#define CONFIG_H

#include <QColor>
#include <QUrl>

namespace config{
    using tick = unsigned;

    namespace game {
        const extern tick query; /**< Time between two query (given in ms) */
        const extern int maxLength; /**< Maximum length the snake can reach before the game ends*/
        const extern QUrl url;
    }

    namespace dimension {
        extern int height;  /**< Height of the board */
        extern int width; /**< Width of the board */
    }

    namespace color {
        extern QColor snakeBodyColor;  /**< Color of the body snake */
        extern QColor snakeHeadColor;  /**< Color of the head snake */
        extern QColor biteColor; /**< Color of the bite */
    }
}

#endif // CONFIG_H

#ifndef CONFIG_H
#define CONFIG_H

namespace config{
    using tick = unsigned;

    namespace gameSpeed {
        const extern tick query; /**< Time between two query (given in ms) */
    }

    namespace dimension {
        extern unsigned height;  /**< Height of the board */
        extern unsigned width; /**< Width of the board */
    }
}

#endif // CONFIG_H

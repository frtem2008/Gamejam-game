//
// Created by livefish on 8/3/24.
//

#ifndef GAMEJAMPROG_WINDOW_H
#define GAMEJAMPROG_WINDOW_H

#include "Base.h"

class Window {
public:
    sf::RenderWindow & win;
    sftools::Chronometer gameClock;
    bool isActive {};

    explicit Window(sf::RenderWindow & win) : win(win) {}
};


#endif //GAMEJAMPROG_WINDOW_H

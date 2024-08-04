//
// Created by livefish on 8/3/24.
//

#ifndef GAMEJAMPROG_WINDOW_H
#define GAMEJAMPROG_WINDOW_H

#include <utility>

#include "Base.h"
#include "external/Chronometer.h"
#include "Game object.h"

class Window {
public:
    sf::RenderWindow & win;
    sftools::Chronometer gameClock;

    bool isActive = true, restartOnNextFrame = false;

    explicit Window(sf::RenderWindow & win) : win(win) {
        gameClock.resume();
    }
};


#endif //GAMEJAMPROG_WINDOW_H

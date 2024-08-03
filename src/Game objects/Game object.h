//
// Created by livefish on 8/3/24.
//

#ifndef GAMEJAMPROG_GAME_OBJECT_H
#define GAMEJAMPROG_GAME_OBJECT_H

#include "Base.h"

class GameObject {
public:
    GameObject() = delete;
    GameObject(const sf::Time & startTime, const sf::Time & endTime) : startTime(startTime), endTime(endTime) {}

    virtual void tick(Window & win) = 0;
    virtual void draw(Window & win) = 0;
    virtual ~GameObject() = default;
    sf::Time startTime, endTime;
};

#endif //GAMEJAMPROG_GAME_OBJECT_H

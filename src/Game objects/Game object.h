//
// Created by livefish on 8/3/24.
//

#ifndef GAMEJAMPROG_GAME_OBJECT_H
#define GAMEJAMPROG_GAME_OBJECT_H

#include "Base.h"
#include "Animation.h"

class Window;

class GameObject {
public:
    GameObject(const sf::Time & startTime, const sf::Time & endTime) : startTime(startTime), endTime(endTime) {}

    virtual bool tryTick(Window & win, std::vector<std::unique_ptr<GameObject>> & gameObjects) final;
    virtual void tryDraw(Window & win) final;

    virtual ~GameObject() = default;

private:
    sf::Time startTime, endTime;
    bool shown = false, expired = false;

    [[nodiscard]] bool available(const Window & win) const;

    virtual void onShow(Window & win) {};

    virtual void onHide(Window & win) {};

    virtual void tick(Window & win, std::vector<std::unique_ptr<GameObject>> & gameObjects) = 0;
    virtual void draw(Window & win) = 0;
};

#endif //GAMEJAMPROG_GAME_OBJECT_H

//
// Created by livefish on 8/3/24.
//

#ifndef GAMEJAMPROG_GAME_OBJECT_H
#define GAMEJAMPROG_GAME_OBJECT_H

#include "Base.h"
#include "drawing/Animation.h"

class Window;

class GameObject {
public:
    using gameObjectVec = std::vector<std::unique_ptr<GameObject>>;

    GameObject(const sf::Time & startTime, const sf::Time & endTime) : startTime(startTime), endTime(endTime) {}

    virtual bool tryTick(Window & win, gameObjectVec &gameObjects) final;
    virtual void tryDraw(Window & win) final;

    virtual ~GameObject() = default;

protected:
    sf::Time startTime, endTime;
private:
    bool shown = false, expired = false;

    [[nodiscard]] bool available(const Window & win) const;

    virtual void onShow(Window & win) {};

    virtual void onHide(Window & win) {};

    virtual void tick(Window & win, gameObjectVec &gameObjects) = 0;
    virtual void draw(Window & win) = 0;
};

using gameObjectVec = std::vector<std::unique_ptr<GameObject>>;

#endif //GAMEJAMPROG_GAME_OBJECT_H

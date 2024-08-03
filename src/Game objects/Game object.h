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
    GameObject() = delete;

    GameObject(const sf::Time & startTime, const sf::Time & endTime) : startTime(startTime), endTime(endTime) {}

    virtual void tryTick(Window & win) final {
        bool avail = available(win);
        if (avail) {
            tick(win);
        }

        if (avail && !shown) {
            shown = true;
            onShow(win);
        }
        if (!avail && shown) {
            shown = false;
            onHide(win);
        }
    };

    virtual void tryDraw(Window & win) final {
        if (available(win)) {
            draw(win);
        }
    }


    virtual ~GameObject() = default;

private:
    sf::Time startTime, endTime;
    bool shown = false;

    [[nodiscard]] bool available(const Window & win) const {
        return startTime <= win.gameClock.getElapsedTime() &&
               win.gameClock.getElapsedTime() <= endTime;
    };

    virtual void onShow(Window & win) {};
    virtual void onHide(Window & win) {};

    virtual void tick(Window & win) = 0;
    virtual void draw(Window & win) = 0;
};

#endif //GAMEJAMPROG_GAME_OBJECT_H

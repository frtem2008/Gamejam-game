//
// Created by livefish on 8/4/24.
//
#include "Game object.h"
#include "Window.h"

bool GameObject::available(const Window & win) const {
    return startTime <= win.gameClock.getElapsedTime() &&
           win.gameClock.getElapsedTime() <= endTime;
}

bool GameObject::tryTick(Window & win, gameObjectVec &gameObjects) {
    bool avail = available(win);

    if (avail && !shown) {
        shown = true;
        onShow(win);
    }

    if (!avail && shown) {
        shown = false;
        onHide(win);
        expired = true;
    }

    if (avail) {
        tick(win, gameObjects);
    }

    return expired;
}

void GameObject::tryDraw(Window & win) {
    if (available(win)) {
        draw(win);
    }
}

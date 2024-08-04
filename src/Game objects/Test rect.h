//
// Created by livefish on 8/3/24.
//

#ifndef GAMEJAMPROG_TEST_RECT_H
#define GAMEJAMPROG_TEST_RECT_H

#include "Game object.h"

class TestRect : public GameObject {
public:
    TestRect(const sf::Time & startTime, const sf::Time & endTime) : GameObject(startTime, endTime) {
        shape.setPosition(50, 50);
        shape.setFillColor(sf::Color::Red);
        shape.setSize({100, 20});
    }

    void tick(Window & win, gameObjectVec &gameObjects) override {
        shape.move({1, 0});
    }

    void draw(Window & win) override {
        win.win.draw(shape);
    }

    sf::RectangleShape shape;
};

#endif //GAMEJAMPROG_TEST_RECT_H

//
// Created by livefish on 8/4/24.
//

#ifndef GAMEJAMPROG_ANIMATEDRECTANGLE_H
#define GAMEJAMPROG_ANIMATEDRECTANGLE_H

#include "Game object.h"

class AnimatedRectangle : public GameObject {
public:
    AnimatedRectangle(const std::string & texPath, int fps, int rows, int columns, int frameCount,
                      sf::Vector2f pos, const sf::Time & startTime, const sf::Time & endTime
    ) : GameObject(startTime, endTime), animation(fps, texPath, rows, columns, frameCount) {
        shape.setPosition(pos);

        animation.update();
        shape.setSize(sf::Vector2f(animation.curFrame()->getSize().x, animation.curFrame()->getSize().y));
    }

private:
    void tick(Window & win, gameObjectVec & gameObjects) override {
        animation.update();
        shape.setTexture(animation.curFrame());
    }

    void draw(Window & win) override {
        win.win.draw(shape);
    }

private:
    sf::RectangleShape shape;
    Animation animation;
};

#endif //GAMEJAMPROG_ANIMATEDRECTANGLE_H

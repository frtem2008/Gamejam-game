//
// Created by natal on 06.08.2024.
//

#ifndef GAMEJAMPROG_END_H
#define GAMEJAMPROG_END_H

#include "common/RoundObject.h"

namespace slava {
    class End : public GameObject, public RoundObject {
    public:
        End(const sf::Time & startTime, const sf::Time & endTime, float x, sf::Vector2f speed)
                : GameObject(startTime, endTime), RoundObject(sprite), x(x), speed(speed) {
            sprite.setPosition(x, 0);
            sprite.setScale(7, 13);
            texture.loadFromFile("../bin/livefish/first/asteroids/big.png");
            sprite.setTexture(texture);
        }

        void tick(Window & win, gameObjectVec & gameObjects) override {
            sprite.move(speed);
        }

        void draw(Window & win) override {
            win.win.draw(sprite);
        }

        sf::Sprite sprite;
        sf::Texture texture;
        float x;
        sf::Vector2f speed;
    };
}
#endif //GAMEJAMPROG_END_H

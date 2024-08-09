//
// Created by natal on 04.08.2024.
//

#ifndef GAMEJAMPROG_FIREBALL_H
#define GAMEJAMPROG_FIREBALL_H

#include "Game object.h"
#include "common/RoundObject.h"

namespace  slava{
    class FireBall : public GameObject, public RoundObject {
    public:
        sf::Vector2f speed;

        FireBall(const sf::Time & startTime, const sf::Time & endTime,
                 sf::Vector2f speed)
                : GameObject(startTime, endTime), RoundObject(sprite), speed(speed){

            sprite.setPosition(630, 50);
            texture.loadFromFile("../bin/Slava/Boll.png");
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
    };
}
#endif //GAMEJAMPROG_FIREBALL_H

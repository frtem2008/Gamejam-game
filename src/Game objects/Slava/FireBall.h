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
        FireBall(const sf::Time & startTime, const sf::Time & endTime,
                 sf::Vector2f speed)
                : GameObject(startTime, endTime), RoundObject(sprite), speed(speed){

            sprite.setPosition(630, 50);
            texture.loadFromFile("../bin/Slava/Boll.png");
            boom.loadFromFile("../bin/Slava/Boom.png");
            sprite.setTexture(texture);
        }

        void tick(Window & win, gameObjectVec & gameObjects) override {
            if(sprite.getPosition().y >= 550){
                sprite.setScale(2,2);
                sprite.setTexture(boom);
            }else{
                sprite.move(speed);
            };

        }

        void draw(Window & win) override {
            win.win.draw(sprite);
        }

        sf::Sprite sprite;
        sf::Texture texture;
        sf::Vector2f speed;
        sf::Texture boom;
    };
}
#endif //GAMEJAMPROG_FIREBALL_H

//
// Created by livefish on 8/4/24.
//

#ifndef GAMEJAMPROG_ASTEROID_H
#define GAMEJAMPROG_ASTEROID_H

#include "Game object.h"
#include "common/RoundObject.h"

namespace fish {
    class Asteroid : public GameObject, public RoundObject {
    public:
        Asteroid(sf::Vector2f xInterval, sf::Vector2f yInterval,
                 sf::Vector2f angVelInterval, sf::Vector2f velXInterval, sf::Vector2f velYInterval,
                 const sf::Time & startTime, const sf::Time & endTime
        ) : GameObject(startTime, endTime), RoundObject(sprite) {
            std::string filenames[] = {"medium", "small", "tiny"};;
            tex.loadFromFile("../bin/livefish/first/asteroids/" +
                             filenames[randomValue<int>({0, 2})] + ".png");

            sprite.setTexture(tex);
            sprite.setPosition(randomValue(xInterval), randomValue(yInterval));

            angVel = randomValue(angVelInterval);
            speed = {randomValue(velXInterval), randomValue(velYInterval)};

            sprite.setOrigin(tex.getSize().x / 2, tex.getSize().y / 2);
        }

        sf::Sprite sprite;

    private:
        void tick(Window & win, gameObjectVec & gameObjects) override {
            sprite.move(speed);
            sprite.rotate(angVel);
        }

        void draw(Window & win) override {
            win.win.draw(sprite);
        }


    private:
        sf::Vector2f speed;
        sf::Texture tex;

        float angVel {};
    };
}

#endif //GAMEJAMPROG_ASTEROID_H

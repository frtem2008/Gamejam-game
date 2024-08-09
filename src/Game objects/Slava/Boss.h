//
// Created by natal on 04.08.2024.
//

#ifndef GAMEJAMPROG_BOSS_H
#define GAMEJAMPROG_BOSS_H

#include "Game object.h"

namespace slava {
    class Boss : public GameObject {
    public:
        Boss(const sf::Time & startTime, const sf::Time & endTime)
                : GameObject(startTime, endTime) {
            texSprite.loadFromFile("../bin/Slava/Boss.png");
            sprite.setTexture(texSprite);

            sprite.setOrigin(12, 10);
            sprite.setScale(10, 10);

            sprite.setPosition(711, -100);
        }

        sf::Sprite sprite;

    private:
        void tick(Window & win, gameObjectVec & gameObjects) override {
            float sinceStart = (win.gameClock.getElapsedTime() - startTime).asSeconds();
            sf::Vector2f corner = sprite.getPosition() - sprite.getOrigin() * sprite.getScale().y;

            if (isTimeIn(2, sinceStart, 2.5)) {
                sprite.move(0, 8);
            }

            if (isTimeIn(12, sinceStart, 13)) {
                sprite.move(0, -5);
            }
            if (corner.y < -250 && sinceStart > 3) {
                sprite.setPosition(1582, 760);
            }

            if (isTimeIn(13, sinceStart, 15)) {
                sprite.move(-25, 0);
            }
            if (corner.x < -250) {
                sprite.setPosition(-110, 360);
            }

            if (isTimeIn(15, sinceStart, 16.1)) {
                sprite.setScale(-10, 10);
                sprite.move(25, 0);
            }
            if (corner.x > 1423) {
                sprite.setScale(10, 10);
                sprite.setPosition(770, 90);
            }

            if (isTimeIn(19, sinceStart, 25)) {
                sprite.move(0, -5);
            }
        }

        void draw(Window & win) override {
            win.win.draw(sprite);
        }

        sf::Texture texSprite;
    };
}

#endif //GAMEJAMPROG_BOSS_H

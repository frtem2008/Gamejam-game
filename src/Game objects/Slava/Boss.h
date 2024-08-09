//
// Created by natal on 04.08.2024.
//

#ifndef GAMEJAMPROG_BOSS_H
#define GAMEJAMPROG_BOSS_H

#include "Game object.h"

namespace slava {
    class Boss : public GameObject, public RoundObject {
    public:
        Boss(const sf::Time & startTime, const sf::Time & endTime)
                : GameObject(startTime, endTime), RoundObject(sprite) {
            sprite.setPosition(610, -50);
            texSprite.loadFromFile("../bin/Slava/Boss.png");
            texSpriteFlip.loadFromFile("../bin/Slava/Boss_flip.png");
            sprite.setTexture(texSprite);
            sprite.setScale(10, 10);
        }

        void tick(Window & win, gameObjectVec & gameObjects) override {
            float remainingLifetime = (endTime - win.gameClock.getElapsedTime()).asSeconds();
            if (12 <= remainingLifetime && remainingLifetime < 13) {
                std::cout << "1\n";
                sprite.move(0, -5);
            }
            if (sprite.getPosition().y < -250) {
                sprite.setPosition(1422, 600);
            }
            if (10 <= remainingLifetime && remainingLifetime < 12) {
                std::cout << "2\n";
                sprite.move(-25, 0);
            }
            if (sprite.getPosition().x < -250) {
                sprite.setPosition(-250, 200);
            }
            if (8.9 <= remainingLifetime && remainingLifetime < 10) {
                std::cout << "3\n";
                sprite.setTexture(texSpriteFlip);
                sprite.move(25, 0);
            }
            if (sprite.getPosition().x > 1423) {
                sprite.setPosition(610, -50);
            }
            if (0 <= remainingLifetime && remainingLifetime <= 6) {
                std::cout << "4\n";
                sprite.move(0, -5);
            }
        }

        void draw(Window & win) override {
            win.win.draw(sprite);
        }

        sf::Sprite sprite;
        sf::Texture texSprite;
        sf::Texture texSpriteFlip;

    };

}
#endif //GAMEJAMPROG_BOSS_H

//
// Created by natal on 04.08.2024.
//

#ifndef GAMEJAMPROG_BOSS_H
#define GAMEJAMPROG_BOSS_H

#include "Game object.h"

namespace slava {
    class Boss : public GameObject {
    public:
        Boss(const sf::Time & startTime, const sf::Time & endTime) : GameObject(startTime, endTime) {
            enemy.setPosition(610, -50);
            texSprite.loadFromFile("../bin/Slava/Boss.png");
            texSpriteFlip.loadFromFile("../bin/Slava/Boss_flip.png");
            enemy.setTexture(texSprite);
            enemy.setScale(10, 10);

        }

        void tick(Window & win, gameObjectVec & gameObjects) override {
            float remainingLifetime = (endTime - win.gameClock.getElapsedTime()).asSeconds();
            if (12 <= remainingLifetime && remainingLifetime < 13) {
                std::cout << "1\n";
                enemy.move(0, -5);
            }
            if (enemy.getPosition().y < -250) {
                enemy.setPosition(1422, 600);
            }
            if (10 <= remainingLifetime && remainingLifetime < 12) {
                std::cout << "2\n";
                enemy.move(-25, 0);
            }
            if (enemy.getPosition().x < -250) {
                enemy.setPosition(-250, 200);
            }
            if (8.9 <= remainingLifetime && remainingLifetime < 10) {
                std::cout << "3\n";
                enemy.setTexture(texSpriteFlip);
                enemy.move(25, 0);
            }
            if (enemy.getPosition().x > 1423) {
                enemy.setPosition(610, -50);
            }
            if (0 <= remainingLifetime && remainingLifetime <= 6) {
                std::cout << "4\n";
                enemy.move(0, -5);
            }
        }

        float distance(sf::Vector2f pos2) {
            sf::Vector2f pos = enemy.getGlobalBounds().getPosition() + enemy.getOrigin() / 2.f;
            return sqrtf((pos.x - pos2.x) * (pos.x - pos2.x) + (pos.y - pos2.y) * (pos.y - pos2.y));
        }

        float radius() {
            return enemy.getGlobalBounds().height / 2;
        }

        void draw(Window & win) override {
            win.win.draw(enemy);
        }

        sf::Sprite enemy;
        sf::Texture texSprite;
        sf::Texture texSpriteFlip;

    };

}
#endif //GAMEJAMPROG_BOSS_H

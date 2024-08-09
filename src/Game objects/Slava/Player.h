//
// Created by natal on 03.08.2024.
//

#ifndef GAMEJAMPROG_PLAYER_H
#define GAMEJAMPROG_PLAYER_H

#include "FireBall.h"
#include "Game object.h"
#include "Wall.h"
#include "Boss.h"
#include "End.h"

namespace slava {
    class Player : public GameObject {
    public:
        Player(const sf::Time & startTime, const sf::Time & endTime) : GameObject(startTime, endTime) {
            right.loadFromFile("../bin/Slava/Player.png");
            sprite.setPosition(50, 400);//Игрок
            sprite.setOrigin(16, 16);
            sprite.setScale(1.5, 1.5);
            sprite.setTexture(right);
        }

        void tick(Window & win, gameObjectVec & gameObjects) override {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && sprite.getGlobalBounds().top > 0) {
                sprite.move(0, -8);
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && sprite.getPosition().y < 800) {
                sprite.move(0, 8);
            }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && sprite.getPosition().x < 1422) {
                sprite.move(8, 0);
                sprite.setScale(1.5, 1.5);
            }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && sprite.getGlobalBounds().left > 0) {
                sprite.move(-8, 0);
                sprite.setScale(-1.5, 1.5);
            }

            for (auto & obj : gameObjects) {
                onCollide<FireBall>(win, sprite, obj, [&win]() { win.restartOnNextFrame = true; });
                onCollide<Wall>(win, sprite, obj, [&win]() { win.restartOnNextFrame = true; });
                onCollide<Boss>(win, sprite, obj, [&win]() { win.restartOnNextFrame = true; });
            }
        }

        void draw(Window & win) override {
            win.win.draw(sprite);
        }

        sf::Sprite sprite;
        sf::Texture texture;
        sf::Texture right;
    };
};

#endif //GAMEJAMPROG_PLAYER_H

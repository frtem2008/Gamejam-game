//
// Created by natal on 03.08.2024.
//

#ifndef GAMEJAMPROG_PLAYER_H
#define GAMEJAMPROG_PLAYER_H

#include "FireBall.h"
#include "Game object.h"
#include "Laser.h"
namespace slava {
    class Player : public GameObject {
    public:
        Player(const sf::Time & startTime, const sf::Time & endTime) : GameObject(startTime, endTime) {
            left.loadFromFile("../bin/Slava/Player_flip.png");
            right.loadFromFile("../bin/Slava/Player.png");
            sprite.setPosition(50, 400);//Игрок
            sprite.setOrigin(16,16);
            sprite.setScale(1.5,1.5);

            sprite.setTexture(right);
        }
        void tick(Window & win, gameObjectVec & gameObjects) override {
           if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && sprite.getGlobalBounds().top > 0 ) {
                sprite.move(0, -8);
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && sprite.getPosition().y < 800) {
                sprite.move(0, 8);
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && sprite.getPosition().x < 1422) {
                sprite.move(8, 0);
                sprite.setTexture(right);
            }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && sprite.getGlobalBounds().left >0) {
                sprite.move(-8, 0);
                sprite.setTexture(left);
            }
            for (auto & obj : gameObjects) {
                if (astrCollides(win, obj)) {
                    win.restartOnNextFrame = true;
                }
                if (laserCollides(win, obj)) {
                    win.restartOnNextFrame = true;
                }
            }
        }
        bool laserCollides(Window & win, std::unique_ptr<GameObject> & obj) {
            Laser * astr;
            if ((astr = dynamic_cast<Laser *>(obj.get()))) {
                sf::Vector2f playerCenter =
                        sprite.getGlobalBounds().getPosition() + sprite.getOrigin() / 2.f;
                float playerRadius = sprite.getGlobalBounds().height / 2;

                if (astr->onScreen(win) && astr->distance(playerCenter) * 1.5 <= astr->radius() + playerRadius) {
                    return true;
                }
            }
            return false;
        }
        bool astrCollides(Window & win, std::unique_ptr<GameObject> & obj) {
            FireBall * astr;
            if ((astr = dynamic_cast<FireBall *>(obj.get()))) {
                sf::Vector2f playerCenter =
                        sprite.getGlobalBounds().getPosition() + sprite.getOrigin() / 2.f;
                float playerRadius = sprite.getGlobalBounds().height / 2;

                if (astr->onScreen(win) && astr->distance(playerCenter) * 1.5 <= astr->radius() + playerRadius) {
                    return true;
                }
            }
            return false;
        }
        void draw(Window & win) override {
            win.win.draw(sprite);
        }
        //переменные
        sf::Sprite sprite;
        sf::Texture texture;
        sf::Texture right, left;
    };
};

#endif //GAMEJAMPROG_PLAYER_H

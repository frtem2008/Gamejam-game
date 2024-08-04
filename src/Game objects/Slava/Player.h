//
// Created by natal on 03.08.2024.
//

#ifndef GAMEJAMPROG_PLAYER_H
#define GAMEJAMPROG_PLAYER_H

#include <iostream>
#include <ctime>
#include <list>
#include "FireBall.h"
#include "Game object.h"

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

            livesFont.loadFromFile("../bin/font.ttf");
            livesText.setFont(livesFont);
            livesText.setStyle(sf::Text::Style::Underlined);
            livesText.setCharacterSize(16);
            livesText.setPosition(100, 0);

            bgTexture.loadFromFile("../bin/Slava/Bg_Slava.png");
            bg.setTexture(bgTexture);
            bg.setPosition(0, 0);
            bg.setScale(2,2);
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
            }
            livesText.setString("Lives: " + std::to_string(lives));
        }
        float distance(sf::Vector2f pos2) {
            sf::Vector2f pos = sprite.getGlobalBounds().getPosition() + sprite.getOrigin() / 2.f;
            return sqrtf((pos.x - pos2.x) * (pos.x - pos2.x) + (pos.y - pos2.y) * (pos.y - pos2.y));
        }
        float radius() {
            return sprite.getGlobalBounds().height / 2;
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
            win.win.draw(bg);
            win.win.draw(sprite);
        }
        //переменные
        sf::Sprite sprite;
        sf::Texture texture;

        int lives = 3;
        sf::Text livesText;
        sf::Font livesFont;

        sf::Texture bgTexture;
        sf::Sprite bg;
        sf::Texture right, left;
    };
};

#endif //GAMEJAMPROG_PLAYER_H

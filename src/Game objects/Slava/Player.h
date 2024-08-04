//
// Created by natal on 03.08.2024.
//

#ifndef GAMEJAMPROG_PLAYER_H
#define GAMEJAMPROG_PLAYER_H

#include <iostream>
#include <ctime>
#include <list>

#include "Game object.h"

namespace slava {
    class FireBall : public GameObject {
    public:
        sf::Vector2f speed;

        FireBall(const sf::Time & startTime, const sf::Time & endTime,
                 sf::Vector2f speed)
                : GameObject(startTime, endTime), speed(speed){

            sprite.setPosition(500, 50);//Игрок
            texture.loadFromFile("../bin/livefish/first/asteroids/medium.png");
            sprite.setTexture(texture);

        }


        void tick(Window & win, gameObjectVec & gameObjects) override {
            sprite.move(speed);

        }
        void draw(Window & win) override {
            win.win.draw(sprite);
        }

        bool onScreen(Window & win) {
            auto view = win.win.getView();
            auto center = view.getCenter();
            auto size = view.getSize();

            return sprite.getGlobalBounds().intersects(
                    sf::FloatRect(center - size / 2.f, size)
            );
        }

        float distance(sf::Vector2f pos2) {
            sf::Vector2f pos = sprite.getGlobalBounds().getPosition() + sprite.getOrigin() / 2.f;
            return sqrtf((pos.x - pos2.x) * (pos.x - pos2.x) + (pos.y - pos2.y) * (pos.y - pos2.y));
        }

        float radius() {
            return sprite.getGlobalBounds().height / 2;
        }




        sf::Sprite sprite;
        sf::Texture texture;
    };
    class Player : public GameObject {
    public:
        Player(const sf::Time & startTime, const sf::Time & endTime) : GameObject(startTime, endTime) {
            sprite.setPosition(50, 50);//Игрок
            sprite.setOrigin(16,16);
            texture.loadFromFile("../bin/Player.png");
            sprite.setTexture(texture);

            livesFont.loadFromFile("../bin/font.ttf");
            livesText.setFont(livesFont);
            livesText.setStyle(sf::Text::Style::Underlined);
            livesText.setCharacterSize(16);
            livesText.setPosition(100, 0);

            bgTexture.loadFromFile("../bin/Bg_Slava.png");
            bg.setTexture(bgTexture);
            bg.setPosition(0, 0);
            bg.setScale(2,2);
        }

        void tick(Window & win, gameObjectVec & gameObjects) override {
            std::cout << sprite.getPosition().y <<"|"<<sprite.getPosition().x<< std::endl;
           if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) and sprite.getGlobalBounds().top > 0 ) {
                sprite.move(0, -8);
            }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) and sprite.getPosition().y < 800) {
                sprite.move(0, 8);
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)and sprite.getPosition().x < 1422) {
                sprite.move(8, 0);
            }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)and sprite.getGlobalBounds().left >0) {
                sprite.move(-8, 0);
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

    };

    class Boss : public GameObject {
    public:
        Boss(const sf::Time & startTime, const sf::Time & endTime) : GameObject(startTime, endTime) {
            enemy.setPosition(550, -100);//Фаерболл
            enemy.setFillColor(sf::Color::Green);
            enemy.setRadius(100);
        }

        void tick(Window & win, gameObjectVec & gameObjects) override {
        }

        void draw(Window & win) override {
            win.win.draw(enemy);
        }


        sf::CircleShape enemy;
    };



};

#endif //GAMEJAMPROG_PLAYER_H

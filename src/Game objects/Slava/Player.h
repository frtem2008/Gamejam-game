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
    class Player : public GameObject {
    public:
        Player(const sf::Time & startTime, const sf::Time & endTime) : GameObject(startTime, endTime) {
            sprite.setPosition(50, 50);//Игрок
            texture.loadFromFile("../bin/Player.png");
            sprite.setTexture(texture);


            shape.setPosition(120, 100);
            shape.setFillColor(sf::Color::White);
            shape.setSize(sf::Vector2f(10, 10));
        }

        void tick(Window & win) override {
           if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
                sprite.move(0, -8);
            }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
                sprite.move(0, 8);
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
                sprite.move(8, 0);
            }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
                sprite.move(-8, 0);
            }

            if (!sprite.getGlobalBounds().intersects(shape.getGlobalBounds())) {
                std::cout << "not colision" << std::endl;
            } else {
                std::cout << "colision" << std::endl;
            }
        }


        void draw(Window & win) override {
            win.win.draw(sprite);
            win.win.draw(shape);
        }

        //переменные
        sf::Sprite sprite;
        sf::Texture texture;
        sf::RectangleShape shape;
    };

    class Boss : public GameObject {
    public:
        Boss(const sf::Time & startTime, const sf::Time & endTime) : GameObject(startTime, endTime) {
            enemy.setPosition(550, -100);//Фаерболл
            enemy.setFillColor(sf::Color::Green);
            enemy.setRadius(100);
        }

        void tick(Window & win) override {
        }

        void draw(Window & win) override {
            win.win.draw(enemy);
        }

        sf::CircleShape enemy;
    };

    class FireBall : public GameObject {
    public:
        sf::Vector2f speed;

        FireBall(const sf::Time & startTime, const sf::Time & endTime, sf::Vector2f speed)
                : GameObject(startTime, endTime), speed(speed) {
            shape.setPosition(600, 0);//Фаерболл
            shape.setFillColor(sf::Color::Red);
            shape.setRadius(50);
        }

        void tick(Window & win) override {
            shape.move(speed);
        }

        void draw(Window & win) override {
            win.win.draw(shape);
        }

        sf::CircleShape shape;
    };

};

#endif //GAMEJAMPROG_PLAYER_H

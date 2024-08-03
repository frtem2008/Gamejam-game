//
// Created by natal on 03.08.2024.
//

#ifndef GAMEJAMPROG_PLAYER_H
#define GAMEJAMPROG_PLAYER_H

#include <iostream>
#include <ctime>
#include <conio.h>
#include <windows.h>
#include "Game object.h"

namespace slava {


    class Player : public GameObject {
    public:
        Player(const sf::Time &startTime, const sf::Time &endTime) : GameObject(startTime, endTime) {
            sprite.setPosition(50, 50);//Игрок
            texture.loadFromFile("../bin/Player.png");
            sprite.setTexture(texture);


        }

        void tick(Window &win) override {
            win.win.setFramerateLimit(60);//количество кадров в секунду


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
        }


        void draw(Window &win) override {

            win.win.draw(sprite);

        }
        //переменные


        sf::Sprite sprite;
        sf::Texture texture;


    };

    class Boss : public GameObject {
    public:
        bool i = false;
        Boss(const sf::Time &startTime, const sf::Time &endTime) : GameObject(startTime, endTime) {
            enemy.setPosition(400, -100);//Фаерболл
            enemy.setFillColor(sf::Color::Green);
            enemy.setRadius(100);
            shape.setPosition(1100, y);//Фаерболл
            shape.setFillColor(sf::Color::Red);
            shape.setRadius(50);
        }

        void tick(Window &win) override {
            win.win.setFramerateLimit(60);//количество кадров в секунду

        }


        void draw(Window &win) override {
            win.win.draw(shape);
            win.win.draw(enemy);

        }


        sf::CircleShape shape;
        sf::CircleShape enemy;
        float y = rand() % 800;
    };
    class FireBall : public GameObject {
    public:
        FireBall(const sf::Time &startTime, const sf::Time &endTime,  const Player &player)
                : GameObject(startTime, endTime), player(player) {

            shape.setPosition(450,0);//Фаерболл
            shape.setFillColor(sf::Color::Red);
            shape.setRadius(50);


        }

        void tick(Window &win) override {


        }


        void draw(Window &win) override {
            win.win.draw(shape);
        }
        const Player &player;
        float positionx = player.sprite.getPosition().x;
        float positiony = player.sprite.getPosition().y;

        sf::CircleShape shape;


    };
}

#endif //GAMEJAMPROG_PLAYER_H
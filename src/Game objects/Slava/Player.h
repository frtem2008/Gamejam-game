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

            enemy.setPosition(550, -100);//Фаерболл
            enemy.setFillColor(sf::Color::Green);
            enemy.setRadius(100);



        }
        void tick(Window &win) override {
            win.win.setFramerateLimit(60);//количество кадров в секунду

        }
        void draw(Window &win) override {

            win.win.draw(enemy);

        }
        sf::CircleShape enemy;
    };
    class FireBall : public GameObject {
    public:
        float tomovex ,tomovey;

        int x = 0 ;
        FireBall(const sf::Time &startTime, const sf::Time &endTime,float toMovex,float ToMovey)
                : GameObject(startTime, endTime) {
            shape.setPosition(600, 0);//Фаерболл
            shape.setFillColor(sf::Color::Red);
            shape.setRadius(50);
            tomovex = toMovex;
            tomovey = ToMovey;

        }

        void tick(Window &win) override {
            shape.move(tomovex,tomovey);
        }
        void draw(Window &win) override {
            win.win.draw(shape);

        }
        sf::CircleShape shape;
    };
    class Player_Attack : public GameObject {
    public:


        float posx,posy;
        Player_Attack(const sf::Time &startTime, const sf::Time &endTime,float x,float y)
                : GameObject(startTime, endTime) {
            posx = x;
            posy = y;
            shape.setPosition(posx, posy);//Фаерболл
            shape.setFillColor(sf::Color::White);
            shape.setRadius(50);


        }

        void tick(Window &win) override {

        }
        void draw(Window &win) override {
            win.win.draw(shape);

        }
        sf::CircleShape shape;
    };
}

#endif //GAMEJAMPROG_PLAYER_H

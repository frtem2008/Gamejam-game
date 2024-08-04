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


            shape.setPosition(120, 100);
            shape.setFillColor(sf::Color::White);
            shape.setSize(sf::Vector2f(10, 10));


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
            if(!spriteBound.intersects(shapeBound)){

                std::cout << "not colision"<<std::endl;
            }else{
                std::cout <<"colision"<< std::endl;
            }
        }


        void draw(Window &win) override {

            win.win.draw(sprite);
            win.win.draw(shape);

        }
        //переменные
        sf::Sprite sprite;
        sf::Texture texture;
        sf::RectangleShape shape;

        sf::FloatRect spriteBound = sprite.getGlobalBounds();
        sf::FloatRect shapeBound = shape.getGlobalBounds();



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

};




#endif //GAMEJAMPROG_PLAYER_H

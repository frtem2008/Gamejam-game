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
            enemy.setPosition(610, -100);//Фаерболл
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
    class Boss2 : public GameObject {
    public:
        Boss2(const sf::Time & startTime, const sf::Time & endTime) : GameObject(startTime, endTime) {
            enemy.setPosition(610, -100);//Фаерболл
            enemy.setFillColor(sf::Color::Green);
            enemy.setRadius(100);
        }
        void tick(Window & win, gameObjectVec & gameObjects) override {
                enemy.move(0,-1);
        }

        void draw(Window & win) override {
            win.win.draw(enemy);
        }

        sf::CircleShape enemy;
    };
}
#endif //GAMEJAMPROG_BOSS_H

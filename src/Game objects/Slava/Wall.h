//
// Created by natal on 04.08.2024.
//

#ifndef GAMEJAMPROG_WALL_H
#define GAMEJAMPROG_WALL_H

#include "Game object.h"

namespace slava {
    class Mark : public GameObject {
    public:
        Mark(const sf::Time & startTime, const sf::Time & endTime, float posx, float posy) : GameObject(startTime,
                                                                                                        endTime) {
            mark.setPosition(posx, posy);
            exmark.loadFromFile("../bin/Slava/Exclamation_mark.png");
            mark.setTexture(exmark);
            mark.setScale(0.5, 0.5);
        }

        void tick(Window & win, gameObjectVec & gameObjects) override {

        }

        void draw(Window & win) override {
            win.win.draw(mark);
        }

        sf::Sprite mark;
        sf::Texture exmark;
    };

    class Wall : public GameObject {
    public:
        Wall(const sf::Time & startTime, const sf::Time & endTime, float posx, float posy, sf::Vector2f speed)
                : GameObject(startTime, endTime), speed(speed) {
            sprite.setPosition(posx, posy);
            texture.loadFromFile("../bin/livefish/first/asteroids/big.png");
            sprite.setTexture(texture);
            sprite.setRotation(90);
            sprite.setScale(6, 8);
        }

        void tick(Window & win, gameObjectVec & gameObjects) override {
            sprite.move(speed);
        }

        void draw(Window & win) override {
            win.win.draw(sprite);

        }

        sf::Sprite sprite;
        sf::Texture texture;
        sf::Vector2f speed;
    };
}
#endif //GAMEJAMPROG_WALL_H

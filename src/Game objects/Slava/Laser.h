//
// Created by natal on 04.08.2024.
//

#ifndef GAMEJAMPROG_LASER_H
#define GAMEJAMPROG_LASER_H
#include "Game object.h"
#include <iostream>
#include <ctime>
#include <list>
namespace slava{
    class Laser : public  GameObject{
    public:
        Laser(const sf::Time &startTime, const sf::Time &endTime, float x) : GameObject(startTime, endTime) {


            line.setPosition(350+x, -40);
            texture.loadFromFile("../bin/Slava/Laser.png");
            line.setTexture(texture);

            line.setScale(6,6);
        }
        void tick(Window & win, gameObjectVec & gameObjects) override {

        }
        bool onScreen(Window & win) {
            auto view = win.win.getView();
            auto center = view.getCenter();
            auto size = view.getSize();

            return line.getGlobalBounds().intersects(
                    sf::FloatRect(center - size / 2.f, size)
            );
        }
        float distance(sf::Vector2f pos2) {
            sf::Vector2f pos = line.getGlobalBounds().getPosition() + line.getOrigin() / 2.f;
            return sqrtf((pos.x - pos2.x) * (pos.x - pos2.x) + (pos.y - pos2.y) * (pos.y - pos2.y));
        }
        float radius() {
            return line.getGlobalBounds().height / 2;
        }
        void draw(Window & win) override {
            win.win.draw(line);

        }
        sf::Sprite line;
        sf::Texture texture;
    };
}
#endif //GAMEJAMPROG_LASER_H

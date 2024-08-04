//
// Created by natal on 04.08.2024.
//

#ifndef GAMEJAMPROG_FIREBALL_H
#define GAMEJAMPROG_FIREBALL_H

#include "Game object.h"

namespace  slava{
    class FireBall : public GameObject {
    public:
        sf::Vector2f speed;

        FireBall(const sf::Time & startTime, const sf::Time & endTime,
                 sf::Vector2f speed)
                : GameObject(startTime, endTime), speed(speed){

            sprite.setPosition(630, 50);//Игрок
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
}
#endif //GAMEJAMPROG_FIREBALL_H

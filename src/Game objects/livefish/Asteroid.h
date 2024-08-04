//
// Created by livefish on 8/4/24.
//

#ifndef GAMEJAMPROG_ASTEROID_H
#define GAMEJAMPROG_ASTEROID_H

#include "Game object.h"

namespace fish {
    class Asteroid : public GameObject {
    public:
        Asteroid(sf::Vector2f xInterval, sf::Vector2f yInterval,
                 sf::Vector2f angVelInterval, sf::Vector2f velXInterval, sf::Vector2f velYInterval,
                 const sf::Time & startTime, const sf::Time & endTime
        ) : GameObject(startTime, endTime) {
            std::string filenames[] = {"medium", "small", "tiny"};;
            tex.loadFromFile("../bin/livefish/first/asteroids/" +
                             filenames[randomValue<int>({0, 2})] + ".png");

            sprite.setTexture(tex);
            sprite.setPosition(randomValue(xInterval), randomValue(yInterval));

            angVel = randomValue(angVelInterval);
            speed = {randomValue(velXInterval), randomValue(velYInterval)};

            sprite.setOrigin(tex.getSize().x / 2, tex.getSize().y / 2);
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

    private:
        void tick(Window & win, gameObjectVec & gameObjects) override {
            sprite.move(speed);
            sprite.rotate(angVel);
        }

        void draw(Window & win) override {
            win.win.draw(sprite);
        }


    private:
        sf::Vector2f speed;
        sf::Texture tex;
        sf::Sprite sprite;
        float angVel {};
    };
}

#endif //GAMEJAMPROG_ASTEROID_H

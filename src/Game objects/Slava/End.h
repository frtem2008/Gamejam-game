//
// Created by natal on 06.08.2024.
//

#ifndef GAMEJAMPROG_END_H
#define GAMEJAMPROG_END_H
#include "Game object.h"
namespace slava{
    class End : public GameObject {
    public:
        End(const sf::Time & startTime, const sf::Time & endTime,float x,sf::Vector2f speed) : GameObject(startTime, endTime) ,x(x),speed(speed){
            sprite.setPosition(x, 0);//Игрок
            sprite.setScale(7,13);
            texture.loadFromFile("../bin/livefish/first/asteroids/big.png");
            sprite.setTexture(texture);

        }
        void tick(Window & win, gameObjectVec & gameObjects) override {
            sprite.move(speed);

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

        void draw(Window & win) override {
            win.win.draw(sprite);
        }

        sf::Sprite sprite;
        sf::Texture texture;
        int x;
        sf::Vector2f speed;

    };
}
#endif //GAMEJAMPROG_END_H

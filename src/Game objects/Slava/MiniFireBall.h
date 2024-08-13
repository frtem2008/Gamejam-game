//
// Created by natal on 13.08.2024.
//

#ifndef GAMEJAMPROG_MINIFIREBALL_H
#define GAMEJAMPROG_MINIFIREBALL_H
#include "Game object.h"
namespace slava{
    class MiniFireBall :public GameObject, public RoundObject{
    public:
        MiniFireBall(const sf::Time &startTime, const sf::Time &endTime,
                     float x,float speedx,float speedy) : GameObject(startTime,endTime),RoundObject(sprite),x(x),speedx(speedx),speedy(speedy) {
            sprite.setPosition(x, 550);
            texture.loadFromFile("../bin/Slava/Boll.png");
            sprite.setTexture(texture);
            sprite.setScale(0.5,0.5);
        }
        void tick(Window & win, gameObjectVec & gameObjects) override {
            sprite.move(speedx,speedy);
        }

        void draw(Window & win) override {
            win.win.draw(sprite);
        }
        float x,speedx,speedy;

        sf::Sprite sprite;
        sf::Texture texture;
    };
}
#endif //GAMEJAMPROG_MINIFIREBALL_H

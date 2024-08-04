//
// Created by livefish on 8/4/24.
//

#ifndef GAMEJAMPROG_FLASHINGRECTANGLE_H
#define GAMEJAMPROG_FLASHINGRECTANGLE_H

#include "Game object.h"

class FlashingRectangle : public GameObject {
public:
    FlashingRectangle(sf::Vector2f pos, sf::Vector2f size,
                      sf::Color col, const sf::Time & startTime, sf::Time fullFlashTime
    ) : GameObject(startTime, startTime + fullFlashTime), flashTime(fullFlashTime) {
        shape.setPosition(pos);
        shape.setSize(size);
        shape.setFillColor(col);
    }

    FlashingRectangle(sf::Vector2f pos, const std::string & texPath,
                      const sf::Time & startTime, sf::Time fullFlashTime
    ) : GameObject(startTime, startTime + fullFlashTime), flashTime(fullFlashTime), isSprite(true) {
        sprite.setPosition(pos);
        tex.loadFromFile(texPath);
        sprite.setTexture(tex);
    }

private:
    sf::Sprite sprite;
    sf::RectangleShape shape;
    sf::Texture tex;
    sf::Time flashTime;
    bool isSprite = false;


    void tick(Window & win, gameObjectVec & gameObjects) override {
        sf::Color color;
        if (isSprite) {
            color = sf::Color::White;
        } else {
            color = shape.getFillColor();
        }

        sf::Time time = win.gameClock.getElapsedTime();
        float halfLen = (endTime - startTime).asSeconds() / 2;
        float timeSinceStart = (time - startTime).asSeconds();
        float timeToEnd = (endTime - time).asSeconds();

        color.a = 255;
        if (timeSinceStart < halfLen) {
            color.a *= timeSinceStart / halfLen;
        } else {
            color.a *= timeToEnd /
                       halfLen;
        }

        if (isSprite) {
            sprite.setColor(color);
        } else {
            shape.setFillColor(color);
        }
    }

    void draw(Window & win) override {
        if (isSprite) {
            win.win.draw(sprite);
        } else {
            win.win.draw(shape);
        }
    }
};

#endif //GAMEJAMPROG_FLASHINGRECTANGLE_H

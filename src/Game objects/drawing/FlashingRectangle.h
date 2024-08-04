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
    sf::Clock clock;
    bool isSprite = false;

    void onShow(Window & win) override {
        clock.restart();
    }

    void tick(Window & win, gameObjectVec & gameObjects) override {
        float k, sec = clock.getElapsedTime().asSeconds(), halfTime = flashTime.asSeconds() / 2;
        if (sec < halfTime) {
            k = sec / halfTime;
        } else {
            k = (halfTime - sec) / halfTime;
        }

        if (isSprite) {
            sprite.setColor(sf::Color(255, 255, 255, 255 * k));
        } else {
            sf::Color shapeColor = shape.getFillColor();
            shapeColor.a = 255 * k;
            shape.setFillColor(shapeColor);
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

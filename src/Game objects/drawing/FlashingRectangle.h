//
// Created by livefish on 8/4/24.
//

#ifndef GAMEJAMPROG_FLASHINGRECTANGLE_H
#define GAMEJAMPROG_FLASHINGRECTANGLE_H

#include "Game object.h"
#include "common/Flashing.h"

class FlashingRectangle : public GameObject, public Flashing {
public:
    FlashingRectangle(sf::Vector2f pos, sf::Vector2f size, sf::Color col,
                      sf::Time startTime, sf::Time fadeIn, sf::Time fullBright, sf::Time fadeOut
    ) : GameObject(startTime, startTime + fadeIn + fullBright + fadeOut),
        Flashing(&shape, startTime, fadeIn, fullBright, fadeOut) {
        shape.setPosition(pos);
        shape.setSize(size);
        shape.setFillColor(col);
    }

    FlashingRectangle(sf::Vector2f pos, const std::string & texPath,
                      sf::Time startTime, sf::Time fadeIn, sf::Time fullBright, sf::Time fadeOut
    ) : GameObject(startTime, startTime + fadeIn + fullBright + fadeOut),
        Flashing(&sprite, startTime, fadeIn, fullBright, fadeOut), isSprite(true) {
        sprite.setPosition(pos);
        tex.loadFromFile(texPath);
        sprite.setTexture(tex);
    }

private:
    sf::Sprite sprite;
    sf::RectangleShape shape;
    sf::Texture tex;
    bool isSprite = false;

    void tick(Window & win, gameObjectVec & gameObjects) override {
        updateColor(win);
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

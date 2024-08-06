//
// Created by livefish on 8/4/24.
//

#ifndef GAMEJAMPROG_FLASHINGRECTANGLE_H
#define GAMEJAMPROG_FLASHINGRECTANGLE_H

#include "Game object.h"

class FlashingRectangle : public GameObject {
public:
    FlashingRectangle(sf::Vector2f pos, sf::Vector2f size, sf::Color col,
                      sf::Time startTime, sf::Time fadeIn, sf::Time fullBright, sf::Time fadeOut
    ) : GameObject(startTime, startTime + fadeIn + fullBright + fadeOut),
        fadeIn(fadeIn), fullBright(fullBright), fadeOut(fadeOut) {
        shape.setPosition(pos);
        shape.setSize(size);
        shape.setFillColor(col);
    }

    FlashingRectangle(sf::Vector2f pos, const std::string & texPath,
                      sf::Time startTime, sf::Time fadeIn, sf::Time fullBright, sf::Time fadeOut
    ) : GameObject(startTime, startTime + fadeIn + fullBright + fadeOut),
        fadeIn(fadeIn), fullBright(fullBright), fadeOut(fadeOut), isSprite(true) {
        sprite.setPosition(pos);
        tex.loadFromFile(texPath);
        sprite.setTexture(tex);
    }

private:
    sf::Sprite sprite;
    sf::RectangleShape shape;
    sf::Texture tex;
    sf::Time fadeIn, fullBright, fadeOut;
    bool isSprite = false;

    void tick(Window & win, gameObjectVec & gameObjects) override {
        sf::Color color;
        if (isSprite) {
            color = sf::Color::White;
        } else {
            color = shape.getFillColor();
        }

        sf::Time time = win.gameClock.getElapsedTime();
        sf::Time timeSinceStart = time - startTime;
        sf::Time timeToEnd = endTime - time;

        color.a = 255;
        float k = 0;
        std::string pass = "";
        if (timeSinceStart <= fadeIn) {
            pass = "in";
            k = timeSinceStart / fadeIn;
        } else if (fadeIn < timeSinceStart && timeSinceStart <= fadeIn + fullBright) {
            pass = "full";
            k = 1;
        } else if (fadeIn + fullBright < timeSinceStart && timeSinceStart <= fadeIn + fullBright + fadeOut) {
            pass = "out";
            k = timeToEnd / fadeOut;
        }

        color.a = 255 * k;
        // std::cout << pass << ", color.a: " << static_cast<int>(color.a) << " k: " << k << "\n";

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

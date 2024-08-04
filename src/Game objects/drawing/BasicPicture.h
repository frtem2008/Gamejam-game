//
// Created by livefish on 8/4/24.
//

#ifndef GAMEJAMPROG_BASICPICTURE_H
#define GAMEJAMPROG_BASICPICTURE_H

#include "Game object.h"

class BasicPicture : public GameObject {
public:
    BasicPicture(const std::string & texPath, sf::Vector2f pos,
                 const sf::Time & startTime, const sf::Time & endTime)
            : GameObject(startTime, endTime) {
        tex.loadFromFile(texPath);
        shape.setTexture(&tex);
        shape.setSize(sf::Vector2f(tex.getSize().x, tex.getSize().y));
        shape.setPosition(pos);
    }

private:
    void tick(Window & win, gameObjectVec & gameObjects) override {}

    void draw(Window & win) override {
        win.win.draw(shape);
    }

private:
    sf::RectangleShape shape;
    sf::Texture tex;
};


#endif //GAMEJAMPROG_BASICPICTURE_H

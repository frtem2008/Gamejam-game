//
// Created by natal on 04.08.2024.
//

#ifndef GAMEJAMPROG_WALL_H
#define GAMEJAMPROG_WALL_H
#include "Game object.h"
namespace slava{
    class Mark : public  GameObject{
    public:
        Mark(const sf::Time &startTime, const sf::Time &endTime, float posx, float  posy) : GameObject(startTime, endTime) {
            mark.setPosition(posx, posy);
            texmark.loadFromFile("../bin/Slava/Exclamation_mark.png");
            mark.setTexture(texmark);
            mark.setScale(0.5,0.5);




        }
        void tick(Window & win, gameObjectVec & gameObjects) override {

        }
        void draw(Window & win) override {

            win.win.draw(mark);

        }

        sf::Sprite mark;
        sf::Texture texmark;
    };
    class Wall : public  GameObject{
    public:
        Wall(const sf::Time &startTime, const sf::Time &endTime, float posx, float  posy, sf::Vector2f speed) : GameObject(startTime, endTime), speed(speed) {
            line.setPosition(posx, posy);
            texture.loadFromFile("../bin/livefish/first/asteroids/big.png");
            line.setTexture(texture);
            line.setRotation(90);
            line.setScale(6,8);
        }
        void tick(Window & win, gameObjectVec & gameObjects) override {
            line.move(speed);
        }
        float radius() {
            return line.getGlobalBounds().height / 2;
        }
        float distance(sf::Vector2f pos2) {
            sf::Vector2f pos = line.getGlobalBounds().getPosition() + line.getOrigin();
            return sqrtf((pos.x - pos2.x) * (pos.x - pos2.x) + (pos.y - pos2.y) * (pos.y - pos2.y));
        }
        void draw(Window & win) override {
            win.win.draw(line);

        }
        sf::Sprite line;
        sf::Texture texture;
        sf::Vector2f  speed;
    };
}
#endif //GAMEJAMPROG_WALL_H

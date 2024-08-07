//
// Created by natal on 04.08.2024.
//

#ifndef GAMEJAMPROG_BOSS_H
#define GAMEJAMPROG_BOSS_H
#include "Game object.h"

namespace slava {
    class Boss : public GameObject {
    public:
        Boss(const sf::Time & startTime, const sf::Time & endTime) : GameObject(startTime, endTime) {
            enemy.setPosition(610, -50);//Фаерболл

            texSprite.loadFromFile("../bin/Slava/Boss.png");
            texSpriteFlip.loadFromFile("../bin/Slava/Boss_flip.png");
            enemy.setTexture(texSprite);
            enemy.setScale(10,10);

        }
        void tick(Window & win, gameObjectVec & gameObjects) override {
            if (endTime - win.gameClock.getElapsedTime() < sf::seconds(13) && endTime - win.gameClock.getElapsedTime() >= sf::seconds(12)) {
                enemy.move(0, -5);
            }
            if(enemy.getPosition().y < -250){
                enemy.setPosition(1422,600);
            }
            if (endTime - win.gameClock.getElapsedTime() < sf::seconds(12)&& endTime - win.gameClock.getElapsedTime() >= sf::seconds(10))  {
                enemy.move(-25,0);
            }
            if(enemy.getPosition().x < -250){
                enemy.setPosition(-250,200);
            }
            if (endTime - win.gameClock.getElapsedTime() < sf::seconds(10) && endTime - win.gameClock.getElapsedTime() >= sf::seconds(8.9)) {
                enemy.setTexture(texSpriteFlip);
                enemy.move(25,0);
            }

            if(enemy.getPosition().x > 1423){
                enemy.setPosition(610,-50);
            }
            if (endTime - win.gameClock.getElapsedTime() < sf::seconds(6) && endTime - win.gameClock.getElapsedTime() >= sf::seconds(0)) {
                enemy.move(0, -5);
            }
        }
        float distance(sf::Vector2f pos2) {
            sf::Vector2f pos = enemy.getGlobalBounds().getPosition() + enemy.getOrigin() / 2.f;
            return sqrtf((pos.x - pos2.x) * (pos.x - pos2.x) + (pos.y - pos2.y) * (pos.y - pos2.y));
        }
        float radius() {
            return enemy.getGlobalBounds().height / 2;
        }

        void draw(Window & win) override {
            win.win.draw(enemy);
        }

        sf::Sprite enemy;
        sf::Texture texSprite;
        sf::Texture texSpriteFlip;
        int x = 1;
    };

}
#endif //GAMEJAMPROG_BOSS_H

//
// Created by livefish on 8/3/24.
//

#ifndef GAMEJAMPROG_PLAYER_H
#define GAMEJAMPROG_PLAYER_H

#include "Game object.h"

namespace fish {
    class Player : public GameObject {
    public:
        Player(const std::string & playerTexPath, int fps, int rows, int columns, int frameCount,
               const std::string & backgroundTexPath,
               const sf::Time & startTime, const sf::Time & endTime)
                : GameObject(startTime, endTime),
                  playerAnim(fps, playerTexPath, rows, columns, frameCount) {
            player.setPosition(50, 135 - 16);

            bgTex.loadFromFile(backgroundTexPath);
            bg.setTexture(bgTex);
            bg.setPosition(0, 0);
        }

        void tick(Window & win) override {
            player.move({1, 0});
            playerAnim.update();
            player.setTexture(*playerAnim.curFrame());
        }

        void draw(Window & win) override {
            auto view = win.win.getDefaultView();
            view.setCenter({player.getPosition().x + 100, player.getPosition().y});
            view.zoom(0.25);

            win.win.setView(view);

            win.win.draw(bg);
            win.win.draw(player);
        }

    public:
        sf::Texture bgTex;
        sf::Sprite player, bg;
        Animation playerAnim;
    };
}

#endif //GAMEJAMPROG_PLAYER_H

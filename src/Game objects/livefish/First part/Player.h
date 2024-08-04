//
// Created by livefish on 8/3/24.
//

#ifndef LIVEFISH_GAMEJAMPROG_PLAYER_H
#define LIVEFISH_GAMEJAMPROG_PLAYER_H

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
            using Key = sf::Keyboard::Key;
            if (sf::Keyboard::isKeyPressed(Key::Space)) {
                if (!wasSpacePressed) {
                    if (acceleration == 0) {
                        acceleration = 0.04;
                    } else {
                        acceleration = -acceleration;
                    }
                }
                wasSpacePressed = true;
            } else {
                wasSpacePressed = false;
            }

            velocity = std::min(velocityMax, std::max(-velocityMax, velocity));

            velocity += acceleration;
            player.move({1, velocity});

            player.setOrigin(16, 16);
            player.setRotation(velocity * 50);

            playerAnim.update();
            player.setTexture(*playerAnim.curFrame());
        }

        void draw(Window & win) override {
            auto view = win.win.getDefaultView();
            view.setCenter({player.getPosition().x + 100, 135});
            view.zoom(0.25);
            win.win.setView(view);

            win.win.draw(bg);
            win.win.draw(player);
        }

        void onHide(Window & win) override {
            win.win.setView(win.win.getDefaultView());
        }

    public:
        bool wasSpacePressed = false;
        float velocity = 0, velocityMax = 1.3, acceleration = 0;

        sf::Texture bgTex;
        sf::Sprite player, bg;
        Animation playerAnim;
    };
}

#endif //LIVEFISH_GAMEJAMPROG_PLAYER_H

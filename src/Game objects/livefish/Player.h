//
// Created by livefish on 8/3/24.
//

#ifndef LIVEFISH_GAMEJAMPROG_PLAYER_H
#define LIVEFISH_GAMEJAMPROG_PLAYER_H

#include "Game object.h"

namespace fish {
    class Player : public GameObject, public Animated {
    public:
        Player(const std::string & playerTexPath, int fps, int rows, int columns, int frameCount,
               const sf::Time & startTime, const sf::Time & endTime)
                : GameObject(startTime, endTime),
                  Animated(playerTexPath, fps, rows, columns, frameCount) {
            player.setPosition(100, 135 - 16);
        }

    private:
        bool wasSpacePressed = false;
        float velocity = 0, velocityMax = 1.3, acceleration = 0;

        float velocityX = 1, accelerationX = 0;

        sf::Sprite player;

    private:
        void onHide(Window & win) override {
            win.win.setView(win.win.getDefaultView());
        }

        void tick(Window & win, gameObjectVec & gameObjects) override {
            player.setTexture(*getAndNext());
            movePlayer(win);

            for (auto & obj : gameObjects) {
                onCollide<Asteroid>(win, player, obj, [&win]() { win.restartOnNextFrame = true; });
            }
        }

        void movePlayer(Window & win) {
            if (win.gameClock.getElapsedTime() < endTime - sf::seconds(2)) {
                handleInput();
            } else {
                goStraight();
                if (win.gameClock.getElapsedTime() > endTime - sf::seconds(1)) {
                    accelerationX = 0.1;
                }
            }

            loopOnBoundaries();
            moveAndRotate();
        }

        void goStraight() {
            if (std::abs(velocity) < 0.1) {
                velocity = 0;
                acceleration = 0;
            } else {
                acceleration = std::copysign(0.05f, -velocity);
            }
        }

        void handleInput() {
            using kb = sf::Keyboard;
            if (kb::isKeyPressed(kb::Space)) {
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
        }

        void loopOnBoundaries() {
            if (player.getGlobalBounds().top + player.getGlobalBounds().height > 270 && velocity > 0) {
                player.setPosition(player.getPosition().x, 0 - player.getGlobalBounds().height / 2);
            }

            if (player.getPosition().y < 0 && velocity < 0) {
                player.setPosition(player.getPosition().x, 270);
            }
        }

        void moveAndRotate() {
            velocity = std::min(velocityMax, std::max(-velocityMax, velocity));

            velocity += acceleration;
            velocityX += accelerationX;

            player.move({velocityX, velocity});

            player.setOrigin(16, 16);
            player.setRotation(velocity * 50);
        }

        void draw(Window & win) override {
            setView(win);
            win.win.draw(player);
        }

        void setView(Window & win) {
            auto view = win.win.getDefaultView();
            view.setCenter({200 + 60 * (win.gameClock.getElapsedTime() - startTime).asSeconds(), 135});
            view.zoom(0.20);
            win.win.setView(view);
        }
    };
}

#endif //LIVEFISH_GAMEJAMPROG_PLAYER_H

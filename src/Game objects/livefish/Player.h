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
            bg.setPosition(-20, 0);


            livesFont.loadFromFile("../bin/font.ttf");
            livesText.setFont(livesFont);
            livesText.setStyle(sf::Text::Style::Underlined);
            livesText.setCharacterSize(16);
            livesText.setPosition(100, 0);
        }

        void tick(Window & win, std::vector<std::unique_ptr<GameObject>> & gameObjects) override {
            updatePlayerAnim(win);
            movePlayer(win);

            for (auto & obj : gameObjects) {
                if (astrCollides(win, obj)) {
                    win.restartOnNextFrame = true;
                }
            }

            livesText.setString("Lives: " + std::to_string(lives));
        }

        bool astrCollides(Window & win, std::unique_ptr<GameObject> & obj) {
            Asteroid * astr;

            if ((astr = dynamic_cast<Asteroid *>(obj.get()))) {
                sf::Vector2f playerCenter =
                        player.getGlobalBounds().getPosition() + player.getOrigin() / 2.f;
                float playerRadius = player.getGlobalBounds().height / 2;

                if (astr->onScreen(win) && astr->distance(playerCenter) * 1.5 <= astr->radius() + playerRadius) {
                    return true;
                }
            }

            return false;
        }

        void draw(Window & win) override {
            setView(win);

            win.win.draw(bg);
            win.win.draw(player);

            auto backupView = win.win.getView();
            auto view = win.win.getDefaultView();

            win.win.setView(view);
            win.win.draw(livesText);
            win.win.setView(backupView);
        }

        void onHide(Window & win) override {
            win.win.setView(win.win.getDefaultView());
        }

    public:
        sf::Texture bgTex;
        sf::Sprite bg;

    public:
        bool wasSpacePressed = false;
        float velocity = 0, velocityMax = 1.3, acceleration = 0;

        sf::Sprite player;
        Animation playerAnim;

        int lives = 3;
        sf::Text livesText;
        sf::Font livesFont;

    private:
        void setView(Window & win) {
            auto view = win.win.getDefaultView();
            view.setCenter({player.getPosition().x + 100, 135});
            view.zoom(0.25);
            win.win.setView(view);
        }

        void movePlayer(Window & win) {
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

            if (player.getGlobalBounds().top + player.getGlobalBounds().height > 270 && velocity > 0) {
                player.setPosition(player.getPosition().x, 0 - player.getGlobalBounds().height / 2);
            }

            if (player.getPosition().y < 0 && velocity < 0) {
                player.setPosition(player.getPosition().x, 270);
            }

            velocity = std::min(velocityMax, std::max(-velocityMax, velocity));

            velocity += acceleration;
            player.move({1, velocity});

            player.setOrigin(16, 16);
            player.setRotation(velocity * 50);
        }

        void updatePlayerAnim(Window & win) {
            playerAnim.update();
            player.setTexture(*playerAnim.curFrame());
        }
    };
}

#endif //LIVEFISH_GAMEJAMPROG_PLAYER_H

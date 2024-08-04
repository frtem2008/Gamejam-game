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

            asteroids.resize(20);
            for (auto & asteroid : asteroids) {
                randomAsteroid(asteroid);
            }

            livesFont.loadFromFile("../bin/font.ttf");
            livesText.setFont(livesFont);
            livesText.setStyle(sf::Text::Style::Underlined);
            livesText.setCharacterSize(16);
            livesText.setPosition(100, 0);
        }

        void moveAsteroids(Window & window) {
            for (auto & a : asteroids) {
                if (a.valid) {
                    a.pos += a.speed;
                    a.sprite.setPosition(a.pos);
                    a.sprite.rotate(a.angVel);
                    a.sprite.setOrigin(a.tex.getSize().x / 2, a.tex.getSize().y / 2);
                }
            }
        }

        static double dist(sf::Vector2f v1, sf::Vector2f v2) {
            return sqrt(pow((v1.x - v2.x), 2) + pow((v1.y - v2.y), 2));
        }

        void tick(Window & win) override {
            updatePlayerAnim(win);

            movePlayer(win);

            for (auto & asteroid : asteroids) {
                if (asteroid.valid &&
                    asteroid.sprite.getGlobalBounds().intersects(
                            sf::FloatRect(
                                    win.win.getView().getCenter() - win.win.getView().getSize() / 2.f,
                                    win.win.getView().getSize()
                            )
                    ) &&
                    dist(asteroid.sprite.getPosition() + asteroid.sprite.getOrigin(),
                         player.getPosition() + player.getOrigin()) <
                    asteroid.tex.getSize().y / 2 + player.getTexture()->getSize().y / 2) {
                    lives--;
                    asteroid.valid = false;
                }
            }

            livesText.setString("Lives: " + std::to_string(lives));

            moveAsteroids(win);
        }

        void draw(Window & win) override {
            setView(win);

            win.win.draw(bg);
            win.win.draw(player);

            for (auto & a : asteroids) {
                if (a.valid) {
                    win.win.draw(a.sprite);
                }
            }

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
    public:
        struct Asteroid {
            sf::Vector2f pos;
            sf::Vector2f speed;
            sf::Texture tex;
            sf::Sprite sprite;
            float angVel {};
            bool valid = true;
        };

        static void randomAsteroid(Asteroid & res) {
            std::string filenames[] = {"medium", "small", "tiny"};;
            res.tex.loadFromFile("../bin/livefish/first/asteroids/" +
                                 filenames[std::uniform_int_distribution<>(0, 2)(random_data)] + ".png");
            res.sprite.setTexture(res.tex);
            res.pos = {
                    std::uniform_real_distribution<float>(200, 1200)(random_data),
                    std::uniform_real_distribution<float>(64, 270 - 64)(random_data)
            };
            res.angVel = std::uniform_real_distribution<float>(-0.3, 0.3)(random_data);
            res.speed = {
                    std::uniform_real_distribution<float>(-0.3, 0.1)(random_data),
                    std::uniform_real_distribution<float>(-0.05, 0.05)(random_data)
            };
        }

        std::vector<Asteroid> asteroids;


    private:
        void setView(Window & win) {
            auto view = win.win.getDefaultView();
            view.setCenter({player.getPosition().x + 100, 135});
            view.zoom(0.25);
            win.win.setView(view);
        }

        void movePlayer(Window & win) {
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
        }

        void updatePlayerAnim(Window & win) {
            playerAnim.update();
            player.setTexture(*playerAnim.curFrame());
        }
    };
}

#endif //LIVEFISH_GAMEJAMPROG_PLAYER_H

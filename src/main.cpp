#include "external/Chronometer.h"

#include "Window.h"
#include "Music player.h"

#include "drawing/BasicPicture.h"
#include "drawing/AnimatedRectangle.h"
#include "drawing/BasicText.h"

#include "livefish/Asteroid.h"
#include "livefish/Player.h"

#include "Slava/Player.h"

template<>
    int randomValue<int>(sf::Vector2i interval) {
        return std::uniform_int_distribution<>(interval.x, interval.y)(random_data);
    }

void deferredDelete(gameObjectVec & gameObjects,
                    std::vector<std::unique_ptr<GameObject> *> & toDelete);

void startGame(Window & win, gameObjectVec & gameObjects);

int main() {
    sf::RenderWindow window(
            sf::VideoMode(1422, 800),
            "Afterlife by livefish, Clown_sigma and Moyvaaaa",
            sf::Style::Default
    );

    window.setPosition({878, 83});
    window.setFramerateLimit(60);

    Window win(window);
    gameObjectVec gameObjects;

    startGame(win, gameObjects);

    std::vector<std::unique_ptr<GameObject> *> toDelete;

    while (window.isOpen()) {
        deferredDelete(gameObjects, toDelete);

        sf::Event event {};
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Q) {
                window.close();
            }

            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::R) {
                win.restartOnNextFrame = true;
            }

            if (event.type == sf::Event::LostFocus) {
                win.isActive = false;
                win.gameClock.pause();
            }
            if (event.type == sf::Event::GainedFocus) {
                win.isActive = true;
                win.gameClock.resume();
            }
        }
        window.clear();

        for (auto & g : gameObjects) {
            bool expired = g->tryTick(win, gameObjects);
            if (expired) {
                toDelete.push_back(&g);
            }
        }

        for (auto & g : gameObjects) {
            g->tryDraw(win);
        }

        window.display();

        if (win.restartOnNextFrame) {
            win.restartOnNextFrame = false;
            startGame(win, gameObjects);
        }
    }

    return 0;
}

void deferredDelete(gameObjectVec & gameObjects,
                    std::vector<std::unique_ptr<GameObject> *> & toDelete) {
    auto firstToRemove = std::stable_partition(
            gameObjects.begin(), gameObjects.end(),
            [&toDelete](std::unique_ptr<GameObject> & g) {
                return std::find(toDelete.begin(), toDelete.end(), &g) == toDelete.end();
            }
    );
    std::for_each(firstToRemove, gameObjects.end(), [ ](std::unique_ptr<GameObject> & g) {
        g.reset();
    });
    gameObjects.erase(firstToRemove, gameObjects.end());
    toDelete.clear();
}

void startGame(Window & win, gameObjectVec & gameObjects) {
    sf::Time startTime = sf::seconds(42);
    const sf::Time gameLen = sf::seconds(202);

    win.gameClock.reset(true);
    win.gameClock.add(startTime);

    gameObjects.clear();

    gameObjects.push_back(std::make_unique<MusicPlayer>("../bin/music.mp3", gameLen, startTime));

    // Livefish part
    gameObjects.push_back(std::make_unique<BasicPicture>(
            "../bin/livefish/first/background.png", sf::Vector2f(-20, 0),
            sf::seconds(22), sf::seconds(42)
    ));

    gameObjects.push_back(std::make_unique<fish::Player>(
            "../bin/livefish/first/ship.png", 6, 2, 2, 3,
            sf::seconds(22), sf::seconds(42)
    ));

    for (int i = 0; i < 30; ++i) {
        gameObjects.push_back(std::make_unique<fish::Asteroid>(
                sf::Vector2f(200, 1400), sf::Vector2f(-16.f, 260.f),
                sf::Vector2f(-0.3, 0.3), sf::Vector2f(-0.3, 0.1), sf::Vector2f(-0.05, 0.05),
                sf::seconds(22), sf::seconds(42)
        ));
    }

    //Slava Part
    slava::FireBall fireBall = slava::FireBall(sf::seconds(44), sf::seconds(50),
                                               sf::Vector2f(0, 0));
    gameObjects.push_back(std::make_unique<slava::Player>(
            sf::seconds(42), sf::seconds(65)));
    gameObjects.push_back(std::make_unique<slava::Boss>(
            sf::seconds(42), sf::seconds(65)));
    for (int i = 0; i < 5; i++) {
        gameObjects.push_back(std::make_unique<slava::FireBall>(
                sf::seconds(42), sf::seconds(45),
                sf::Vector2f(-4, i))
        );
    }

    for (int i = -4; i <= 4; i++) {
        gameObjects.push_back(std::make_unique<slava::FireBall>(
                sf::seconds(44), sf::seconds(50),
                sf::Vector2f(i, 4)));
    }

    for (int i = 0; i <= 4; i++) {
        gameObjects.push_back(std::make_unique<slava::FireBall>(
                sf::seconds(48), sf::seconds(53),
                sf::Vector2f(4, i)));
    }

    gameObjects.push_back(std::make_unique<BasicText>(
            "../bin/font.ttf", sf::Text::Style::Underlined, sf::Color::White, sf::Vector2f(0, 0),
            [ ](Window & win, gameObjectVec & gameObjects) -> std::string {
                return std::to_string(win.gameClock.getElapsedTime().asSeconds());
            },
            sf::Time::Zero, gameLen
    ));
}

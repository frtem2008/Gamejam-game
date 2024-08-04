#include "external/Chronometer.h"

#include "Window.h"

#include "Test rect.h"
#include "Music player.h"
#include "Time renderer.h"

#include "livefish/Player.h"

#include "Slava/Player.h"

void defferedDelete(std::vector<std::unique_ptr<GameObject>> & gameObjects,
                    std::vector<std::unique_ptr<GameObject> *> & toDelete);

int main() {
    sf::RenderWindow window(
            sf::VideoMode(1422, 800),
            "Afterlife by livefish, Clown_sigma and Moyvaaaa",
            sf::Style::Default
    );

    window.setPosition({878, 83});
    window.setFramerateLimit(60);

    sf::Time startTime = sf::seconds(20);
    const sf::Time gameLen = sf::seconds(202);

    Window win(window);
    win.gameClock.add(startTime);

    std::vector<std::unique_ptr<GameObject>> gameObjects;

    gameObjects.push_back(std::make_unique<MusicPlayer>("../bin/music.mp3", gameLen, startTime));

    gameObjects.push_back(std::make_unique<fish::Player>(
            "../bin/livefish/first/ship.png", 6, 2, 2, 3,
            "../bin/livefish/first/background.png",
            sf::seconds(22), sf::seconds(42)
    ));

    //Slava Part
    gameObjects.push_back(std::make_unique<slava::Player>(
            sf::seconds(42), sf::seconds(65)));
    gameObjects.push_back(std::make_unique<slava::Boss>(
            sf::seconds(42), sf::seconds(65)));


    for (int i = 0; i < 5; i++) {
        gameObjects.push_back(std::make_unique<slava::FireBall>(
                sf::seconds(42), sf::seconds(45),
                sf::Vector2f(-4, i)
        ));
    }
    for (int i = -4; i <= 4; i++) {
        gameObjects.push_back(std::make_unique<slava::FireBall>(
                sf::seconds(44), sf::seconds(50),
                sf::Vector2f(i, 4)
        ));
    }

    gameObjects.push_back(std::make_unique<TimeRenderer>("../bin/font.ttf", gameLen));

    std::vector<std::unique_ptr<GameObject> *> toDelete;

    while (window.isOpen()) {
        defferedDelete(gameObjects, toDelete);

        sf::Event event {};
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Q) {
                window.close();
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
            bool expired = g->tryTick(win);
            if (expired) {
                toDelete.push_back(&g);
            }
        }

        for (auto & g : gameObjects) {
            g->tryDraw(win);
        }

        window.display();
    }

    return 0;
}

void defferedDelete(std::vector<std::unique_ptr<GameObject>> & gameObjects,
                    std::vector<std::unique_ptr<GameObject> *> & toDelete) {
    auto firstToRemove = std::stable_partition(
            gameObjects.begin(), gameObjects.end(),
            [&toDelete](std::unique_ptr<GameObject> &g) {
                return std::find(toDelete.begin(), toDelete.end(), &g) == toDelete.end();
            }
    );
    std::for_each(firstToRemove, gameObjects.end(), [ ](std::unique_ptr<GameObject> &g) {
        g.reset();
    });
    gameObjects.erase(firstToRemove, gameObjects.end());
    toDelete.clear();
}

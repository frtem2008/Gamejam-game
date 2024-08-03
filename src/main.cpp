#include "external/Chronometer.h"

#include "Window.h"

#include "Test rect.h"
#include "Music player.h"
#include "Time renderer.h"

int main() {
    sf::RenderWindow window(
            sf::VideoMode(1000, 800),
            "Afterlife by livefish, Clown_sigma and Moyvaaaa",
            sf::Style::Default
    );

    window.setPosition({878, 83});
    window.setFramerateLimit(60);

    Window win(window);

    std::vector<std::unique_ptr<GameObject>> gameObjects;
    gameObjects.push_back(std::make_unique<TimeRenderer>("../bin/font.ttf", sf::seconds(202)));
    gameObjects.push_back(std::make_unique<MusicPlayer>("../bin/music.mp3", sf::seconds(202)));
    gameObjects.push_back(std::make_unique<TestRect>(sf::seconds(2), sf::seconds(5)));


    while (window.isOpen()) {
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

        for (auto &g : gameObjects) {
            if (g->startTime <= win.gameClock.getElapsedTime() && win.gameClock.getElapsedTime() <= g->endTime)
                g->tick(win);
        }

        for (auto & g : gameObjects)
            if (g->startTime <= win.gameClock.getElapsedTime() && win.gameClock.getElapsedTime() <= g->endTime)
                g->draw(win);

        window.display();
    }

    return 0;
}

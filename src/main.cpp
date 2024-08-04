#include "external/Chronometer.h"

#include "Window.h"

#include "Test rect.h"
#include "Music player.h"
#include "Time renderer.h"

#include "livefish/First part/Player.h"

#include "Slava/Player.h"

int main() {
    sf::RenderWindow window(
            sf::VideoMode(1422, 800),
            "Afterlife by livefish, Clown_sigma and Moyvaaaa",
            sf::Style::Default
    );

    window.setPosition({878, 83});
    window.setFramerateLimit(60);

    sf::Time startTime = sf::seconds(42);
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

    gameObjects.push_back(std::make_unique<slava::Player>(sf::seconds(42), sf::seconds(65)));
    gameObjects.push_back(std::make_unique<slava::Boss>(sf::seconds(42), sf::seconds(65)));


    int x = 0;






    gameObjects.push_back(std::make_unique<TimeRenderer>("../bin/font.ttf", gameLen));

    while (window.isOpen()) {
        //attack
        if (x == 0){
            for(int i = 0 ;i < 5;i++){
                gameObjects.push_back(std::make_unique<slava::FireBall>(sf::seconds(42), sf::seconds(65),-4,i));
            }
        }
        if (x == 150){
            for(int i = -4 ;i < 5;i++){
                gameObjects.push_back(std::make_unique<slava::FireBall>(sf::seconds(42), sf::seconds(65),i,4));
            }
            x++;
        }else{
            x++;
        }
        if (x == 300){
            for(int i =  0;i < 5;i++){
                gameObjects.push_back(std::make_unique<slava::FireBall>(sf::seconds(42), sf::seconds(65),4,i));
            }
        }
        if (x >= 450 and x < 600){
            for(int i =  -10;i < 10;i++){
                gameObjects.push_back(std::make_unique<slava::FireBall>(sf::seconds(42), sf::seconds(65),i,4));
            }
        }


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
            g->tryTick(win);
        }

        for (auto & g : gameObjects) {
            g->tryDraw(win);
        }

        window.display();

    }

    return 0;
}

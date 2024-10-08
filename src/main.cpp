#include "external/Chronometer.h"

#include "Window.h"
#include "Music player.h"

#include "drawing/BasicPicture.h"
#include "drawing/BasicText.h"

#include "drawing/FlashingRectangle.h"

#include "livefish/Asteroid.h"
#include "livefish/Player.h"

#include "Slava/Player.h"
#include "Slava/Boss.h"
#include "Slava/Wall.h"
#include "Slava/End.h"

template<>
    int randomValue<int>(sf::Vector2i interval) {
        return std::uniform_int_distribution<>(interval.x, interval.y)(random_data);
    }

void deferredDelete(gameObjectVec & gameObjects,
                    std::vector<std::unique_ptr<GameObject> *> & toDelete);

void startGame(Window & win, gameObjectVec & gameObjects);

int main() {
    sf::RenderWindow window(
            sf::VideoMode(1920, 1080),
            "Afterlife by livefish, Clown_sigma and Moyvaaaa",
            sf::Style::None
    );

    window.setPosition({0, 0});
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
    sf::Time startTime = sf::seconds(40);
    const sf::Time gameLen = sf::seconds(202);
    win.gameClock.reset(true);
    win.gameClock.add(startTime);

    gameObjects.clear();

    gameObjects.push_back(std::make_unique<MusicPlayer>("../bin/music.mp3", gameLen, startTime));
    win.win.setView(win.win.getDefaultView());

    // Lerkk part
    gameObjects.push_back(std::make_unique<BasicPicture>(
            "../bin/lerkk/1.png", sf::Vector2f(0, 0),
            sf::seconds(0), sf::seconds(6)
    ));


    // gjapjogs
    gameObjects.push_back(std::make_unique<BasicPicture>(
            "../bin/lerkk/2.png", sf::Vector2f(0, 0),
            sf::seconds(6), sf::seconds(10.3)
    ));
    gameObjects.push_back(std::make_unique<BasicPicture>(
            "../bin/lerkk/3.png", sf::Vector2f(0, 0),
            sf::seconds(10.3), sf::seconds(13)
    ));
    gameObjects.push_back(std::make_unique<BasicPicture>(
            "../bin/lerkk/4.png", sf::Vector2f(0, 0),
            sf::seconds(13), sf::seconds(17)
    ));
    gameObjects.push_back(std::make_unique<BasicPicture>(
            "../bin/lerkk/5.png", sf::Vector2f(0, 0),
            sf::seconds(17), sf::seconds(22)
    ));

    // Livefish part
    gameObjects.push_back(std::make_unique<BasicPicture>(
            "../bin/livefish/first/background.png", sf::Vector2f(-20, 0),
            sf::seconds(22), sf::seconds(40)
    ));

    gameObjects.push_back(std::make_unique<fish::Player>(
            "../bin/livefish/first/ship.png", 6, 2, 2, 3,
            sf::seconds(22), sf::seconds(40)
    ));

    for (int i = 0; i < 23; ++i) {
        gameObjects.push_back(std::make_unique<fish::Asteroid>(
                sf::Vector2f(200, 980), sf::Vector2f(-16.f, 260.f),
                sf::Vector2f(-0.3, 0.3), sf::Vector2f(-0.3, 0.1), sf::Vector2f(-0.05, 0.05),
                sf::seconds(22), sf::seconds(40)
        ));
    }

    //Slava Part

    gameObjects.push_back(std::make_unique<BasicPicture>(
            "../bin/Slava/Bg_Slava.png", sf::Vector2f(-20, 0),
            sf::seconds(40), sf::seconds(65)
    ));
    gameObjects.push_back(std::make_unique<slava::Player>(
            sf::seconds(40), sf::seconds(65)));

    for (int i = 0; i < 5; i++) {
        gameObjects.push_back(std::make_unique<slava::FireBall>(
                sf::seconds(44), sf::seconds(47),
                sf::Vector2f(-4, i))
        );
    }
    for (int i = -4; i <= 4; i++) {
        gameObjects.push_back(std::make_unique<slava::FireBall>(
                sf::seconds(45), sf::seconds(48),
                sf::Vector2f(i, 4)));
    }
    int speed[8][2] = {
            {2,2},
            {0,2},
            {-2,2},
            {-2,0},
            {-2,-2},
            {0,-2},
            {2,-2},
            {2,0}};
    int x5 =0;
    for (int i =-4;i<=4;i++){
        for(int j = 0; j <= 7;j++){
            gameObjects.push_back(std::make_unique<slava::MiniFireBall>(
                    sf::seconds(47), sf::seconds(50),170+x5,speed[j][0],speed[j][1]
            ));
        }
        x5 += 240;
    }



    for (int i = 0; i <= 4; i++) {
        gameObjects.push_back(std::make_unique<slava::FireBall>(
                sf::seconds(46), sf::seconds(53),
                sf::Vector2f(4, i)));
    }
    int y = 0;
    for (int i = 0; i < 2; i++) {
        gameObjects.push_back(std::make_unique<slava::Wall>(
                sf::seconds(40), sf::seconds(48), 1422, 0 + y, sf::Vector2f(-9, 0)));
        y += 500;
    }
    for (int i = -4; i <= 4; i++) {
        gameObjects.push_back(std::make_unique<slava::FireBall>(
                sf::seconds(48), sf::seconds(51),
                sf::Vector2f(i, 4)));
    }
    x5 = 0;
    for (int i =-4;i<=4;i++){
        for(int j = 0; j <= 7;j++){
            gameObjects.push_back(std::make_unique<slava::MiniFireBall>(
                    sf::seconds(50), sf::seconds(53),170+x5,speed[j][0],speed[j][1]
            ));
        }
        x5 += 240;
    }
    int x2 = 0;
    for (int i = 0; i < 2; i++) {
        gameObjects.push_back(std::make_unique<BasicPicture>(
                "../bin/Slava/Exclamation_mark.png", sf::Vector2f(150 + x2, 400),
                sf::seconds(47), sf::seconds(49)
        ));
        gameObjects.push_back(std::make_unique<slava::Wall>(
                sf::seconds(48), sf::seconds(53), 400 + x2, -300, sf::Vector2f(0, 10)));
        x2 += 1000;
    }
    int x3 = -100;
    float x4 = 9;
    for (int i = 0; i < 2; i++) {
        gameObjects.push_back(std::make_unique<slava::End>(
                sf::seconds(64), sf::seconds(65), x3, sf::Vector2f(x4, 0)));
        x4 = -9;
        x3 = 1300;
    }
    gameObjects.push_back(std::make_unique<BasicText>(
            "../bin/font.ttf", sf::Text::Style::Underlined, sf::Color::White,
            sf::Vector2f(711, 350), "I'm tired of you.",
            sf::seconds(50), sf::seconds(52)
    ));
    gameObjects.push_back(std::make_unique<BasicText>(
            "../bin/font.ttf", sf::Text::Style::Underlined, sf::Color::White,
            sf::Vector2f(711, 350), "Okay, let's finish this",
            sf::seconds(59), sf::seconds(62)
    ));
    gameObjects.push_back(std::make_unique<slava::Boss>(
            sf::seconds(40), sf::seconds(65)));
    gameObjects.push_back(std::make_unique<BasicText>(
            "../bin/font.ttf", sf::Text::Style::Underlined, sf::Color::White,
            sf::Vector2f(200, 0), "WASD!",
            sf::seconds(40), sf::seconds(43)
    ));

    // Livefish intermission
    gameObjects.push_back(std::make_unique<FlashingText>(
            "../bin/font.ttf", sf::Text::Style::Underlined, sf::Color::White,
            sf::Vector2f(711, 350), "Livefish intermission gotta be here",
            sf::seconds(65), sf::seconds(4), sf::seconds(3), sf::seconds(4)
    ));
    gameObjects.push_back(std::make_unique<FlashingText>(
            "../bin/font.ttf", sf::Text::Style::Underlined, sf::Color::White,
            sf::Vector2f(711, 350), "Some lore and rules explanation gotta be here",
            sf::seconds(76), sf::seconds(4), sf::seconds(3), sf::seconds(4)
    ));
    gameObjects.push_back(std::make_unique<FlashingText>(
            "../bin/font.ttf", sf::Text::Style::Underlined, sf::Color::White,
            sf::Vector2f(711, 350), "Armor animation here",
            sf::seconds(87), sf::seconds(3), sf::seconds(4), sf::seconds(3)
    ));
    gameObjects.push_back(std::make_unique<FlashingText>(
            "../bin/font.ttf", sf::Text::Style::Underlined, sf::Color::White,
            sf::Vector2f(711, 350), "Black screen fade",
            sf::seconds(97), sf::seconds(2), sf::seconds(2), sf::seconds(2)
    ));
    gameObjects.push_back(std::make_unique<FlashingText>(
            "../bin/font.ttf", sf::Text::Style::Underlined, sf::Color::White,
            sf::Vector2f(711, 350), "3",
            sf::seconds(104), sf::seconds(0.25), sf::seconds(0.5), sf::seconds(0.25)
    ));
    gameObjects.push_back(std::make_unique<FlashingText>(
            "../bin/font.ttf", sf::Text::Style::Underlined, sf::Color::White,
            sf::Vector2f(711, 350), "2",
            sf::seconds(105), sf::seconds(0.25), sf::seconds(0.5), sf::seconds(0.25)
    ));
    gameObjects.push_back(std::make_unique<FlashingText>(
            "../bin/font.ttf", sf::Text::Style::Underlined, sf::Color::White,
            sf::Vector2f(711, 350), "1",
            sf::seconds(106), sf::seconds(0.25), sf::seconds(0.5), sf::seconds(0.25)
    ));
    gameObjects.push_back(std::make_unique<FlashingText>(
            "../bin/font.ttf", sf::Text::Style::Underlined, sf::Color::White,
            sf::Vector2f(711, 350), "AFTERLIFE",
            sf::seconds(107), sf::seconds(0.5), sf::seconds(1.25), sf::seconds(0.25)
    ));

    // Timer
    gameObjects.push_back(std::make_unique<BasicText>(
            "../bin/font.ttf", sf::Text::Style::Underlined, sf::Color::White, sf::Vector2f(0, 0),
            [ ](Window & win, gameObjectVec & gameObjects) -> std::string {
                return std::to_string(win.gameClock.getElapsedTime().asSeconds());
            },
            sf::Time::Zero, gameLen
    ));

    // fade translations
    gameObjects.push_back(std::make_unique<FlashingRectangle>(
            sf::Vector2f(0, 0), sf::Vector2f(1920, 1080),
            sf::Color::Black, sf::seconds(21), sf::seconds(0.8), sf::seconds(0.2), sf::seconds(1)
    ));

    gameObjects.push_back(std::make_unique<FlashingRectangle>(
            sf::Vector2f(0, 0), sf::Vector2f(1920, 1080),
            sf::Color::Black, sf::seconds(32), sf::seconds(0.8), sf::seconds(0.4), sf::seconds(0.8)
    ));

    gameObjects.push_back(std::make_unique<FlashingRectangle>(
            sf::Vector2f(0, 0), sf::Vector2f(1920, 1080),
            sf::Color::Black, sf::seconds(39), sf::seconds(1), sf::seconds(0.7), sf::seconds(0.8)
    ));
}

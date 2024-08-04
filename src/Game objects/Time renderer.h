//
// Created by livefish on 8/3/24.
//

#ifndef GAMEJAMPROG_TIME_RENDERER_H
#define GAMEJAMPROG_TIME_RENDERER_H

#include "Game object.h"

class TimeRenderer : public GameObject {
public:
    TimeRenderer(const std::string & fontPath, sf::Time gameLen) :
            GameObject(sf::Time::Zero, gameLen) {
        font.loadFromFile(fontPath);
        text.setFont(font);
        text.setStyle(sf::Text::Style::Underlined);
        text.setCharacterSize(16);
        text.setPosition(0, 0);
    }

    void tick(Window & win, std::vector<std::unique_ptr<GameObject>> & gameObjects) override {
        text.setString(std::to_string(win.gameClock.getElapsedTime().asSeconds()));
    }

    void draw(Window & win) override {
        auto backupView = win.win.getView();
        auto view = win.win.getDefaultView();

        win.win.setView(view);
        win.win.draw(text);
        win.win.setView(backupView);
    }

private:
    sf::Text text;
    sf::Font font;
};

#endif //GAMEJAMPROG_TIME_RENDERER_H

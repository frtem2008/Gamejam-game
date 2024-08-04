//
// Created by livefish on 8/4/24.
//

#ifndef GAMEJAMPROG_BASICTEXT_H
#define GAMEJAMPROG_BASICTEXT_H

#include <utility>

#include "Game object.h"

class BasicText : public GameObject {
public:
    using stringGeneratorFunction =
            std::function<std::string(Window & win, gameObjectVec & gameObjects)>;

    BasicText(const std::string &fontPath, sf::Uint32 style, sf::Color color, sf::Vector2f pos,
              const sf::Time & startTime, const sf::Time & endTime
    ) : GameObject(startTime, endTime) {
        font.loadFromFile(fontPath);

        text.setPosition(pos);
        text.setFont(font);
        text.setStyle(style);
        text.setFillColor(color);
    }

    BasicText(const std::string & fontPath, sf::Uint32 style, sf::Color color, sf::Vector2f pos,
              stringGeneratorFunction stringGenerator,
              const sf::Time & startTime, const sf::Time & endTime
    ) : BasicText(fontPath, style, color, pos, startTime, endTime) {
        stringGen = std::move(stringGenerator);
    }

    void setString(const std::string & str) {
        stringGen = [str](Window & win, gameObjectVec & gameObjects) {
            return str;
        };
    }

private:
    sf::Font font;
    sf::Text text;
    stringGeneratorFunction stringGen;

    void tick(Window & win, gameObjectVec & gameObjects) override {
        text.setString(stringGen(win, gameObjects));
    }

    void draw(Window & win) override {
        auto backupView = win.win.getView();
        win.win.setView(win.win.getDefaultView());

        win.win.draw(text);
        win.win.setView(backupView);
    }
};

#endif //GAMEJAMPROG_BASICTEXT_H

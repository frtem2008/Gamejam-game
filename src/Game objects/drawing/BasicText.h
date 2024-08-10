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

    BasicText(const std::string & fontPath, sf::Uint32 style, sf::Color color, sf::Vector2f pos,
              const std::string & str,
              const sf::Time & startTime, const sf::Time & endTime
    ) : GameObject(startTime, endTime) {
        font.loadFromFile(fontPath);

        text.setPosition(pos);
        text.setFont(font);
        text.setStyle(style);
        text.setFillColor(color);
        setString(str);
    }

    BasicText(const std::string & fontPath, sf::Uint32 style, sf::Color color, sf::Vector2f pos,
              stringGeneratorFunction stringGenerator,
              const sf::Time & startTime, const sf::Time & endTime
    ) : BasicText(fontPath, style, color, pos, "", startTime, endTime) {
        stringGen = std::move(stringGenerator);
    }

    void setString(const std::string & str) {
        stringGen = [str](Window & win, gameObjectVec & gameObjects) {
            return str;
        };
    }

protected:
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

class FlashingText : public BasicText, public Flashing {
public:
    FlashingText(const std::string & fontPath, sf::Uint32 style, const sf::Color & color, const sf::Vector2f & pos,
                 const std::string & str,
                 sf::Time startTime, sf::Time fadeIn, sf::Time fullBright, sf::Time fadeOut)
            : BasicText(fontPath, style, color, pos, str, startTime, startTime + fadeIn + fullBright + fadeOut),
              Flashing(&coverShape, startTime, fadeIn, fullBright, fadeOut) {
        coverShape.setFillColor(sf::Color::Black);
    }

    FlashingText(const std::string & fontPath, sf::Uint32 style, const sf::Color & color, const sf::Vector2f & pos,
                 const stringGeneratorFunction & stringGenerator,
                 sf::Time startTime, sf::Time fadeIn, sf::Time fullBright, sf::Time fadeOut)
            : BasicText(fontPath, style, color, pos, stringGenerator,
                        startTime, startTime + fadeIn + fullBright + fadeOut),
              Flashing(&coverShape, startTime, fadeIn, fullBright, fadeOut) {
        coverShape.setFillColor(sf::Color::Black);
    }

protected:
    void tick(Window & win, gameObjectVec & gameObjects) override {
        coverShape.setPosition(text.getGlobalBounds().getPosition());
        coverShape.setSize(text.getGlobalBounds().getSize());
        updateColor(win);

        BasicText::tick(win, gameObjects);
    }

    void draw(Window & win) override {
        auto backupView = win.win.getView();
        win.win.setView(win.win.getDefaultView());

        win.win.draw(text);
        win.win.draw(coverShape);

        win.win.setView(backupView);
    }

    sf::RectangleShape coverShape;
};

#endif //GAMEJAMPROG_BASICTEXT_H

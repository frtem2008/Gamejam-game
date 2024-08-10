//
// Created by livefish on 8/10/24.
//

#ifndef GAMEJAMPROG_FLASHING_H
#define GAMEJAMPROG_FLASHING_H

class Flashing {
public:
    Flashing(sf::Sprite * sprite, sf::Time startTime, sf::Time fadeIn, sf::Time fullBright, sf::Time fadeOut)
            : sprite(sprite), startTime(startTime), endTime(startTime + fadeIn + fullBright + fadeOut),
              fadeIn(fadeIn), fullBright(fullBright), fadeOut(fadeOut) {}

    Flashing(sf::Shape * shape, sf::Time startTime, sf::Time fadeIn, sf::Time fullBright, sf::Time fadeOut)
            : shape(shape), startTime(startTime), endTime(startTime + fadeIn + fullBright + fadeOut),
              fadeIn(fadeIn), fullBright(fullBright), fadeOut(fadeOut) {}

    void updateColor(Window & win) {
        sf::Color color = sprite.has_value() ? sf::Color::White : shape.value()->getFillColor();

        sf::Time time = win.gameClock.getElapsedTime();
        sf::Time timeSinceStart = time - startTime;
        sf::Time timeToEnd = endTime - time;

        color.a = 255;
        float k = 0;
        if (timeSinceStart <= fadeIn) {
            k = timeSinceStart / fadeIn;
        } else if (fadeIn < timeSinceStart && timeSinceStart <= fadeIn + fullBright) {
            k = 1;
        } else if (fadeIn + fullBright < timeSinceStart && timeSinceStart <= fadeIn + fullBright + fadeOut) {
            k = timeToEnd / fadeOut;
        }
        color.a = 255 * k;

        sprite.has_value() ? sprite.value()->setColor(color) : shape.value()->setFillColor(color);
    }

    std::optional<sf::Sprite *> sprite;
    std::optional<sf::Shape *> shape;
    sf::Time startTime, endTime, fadeIn, fullBright, fadeOut;
};

#endif //GAMEJAMPROG_FLASHING_H

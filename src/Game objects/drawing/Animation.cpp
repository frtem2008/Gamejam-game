//
// Created by livefish on 8/3/24.
//

#include "Animation.h"

Animation::Animation(double fps, const std::string & spritesheetPath, int rows, int columns, int spriteCount)
        : fps(fps), spritesheet(new sf::Image()), frames(spriteCount) {
    spritesheet->loadFromFile(spritesheetPath);

    int x = 0, y = 0,
            sizeX = static_cast<int>(spritesheet->getSize().x),
            sizeY = static_cast<int>(spritesheet->getSize().y),
            texW = sizeX / rows,
            texH = sizeY / columns;

    for (int i = 0; i < spriteCount; ++i) {
        frames[i] = std::make_unique<sf::Texture>();
        frames[i]->loadFromImage(*spritesheet, sf::IntRect(x, y, texW, texH));
        x = (x + texW) % sizeX;
        if (x == 0 && i != 0) {
            y += texH;
        }
    }
}

sf::Texture * Animation::curFrame() {
    return frames[frame].get();
}

void Animation::update() {
    if (clock.getElapsedTime().asSeconds() > 1.0 / fps) {
        nextFrame();
        clock.restart();
    }
}

Animation Animation::getStaticAnimation(const sf::Texture & singleTexture) {
    Animation res(1, {singleTexture});
    return res;
}

Animation Animation::getStaticAnimation(const std::string & texPath) {
    Animation res(1, {texPath});
    return res;
}

void Animation::nextFrame() {
    frame = (frame + 1) % frames.size();
}

Animation::Animation(double fps, const std::vector<sf::Texture> & textures) : fps(fps) {
    for (auto & tex : textures) {
        frames.push_back(std::make_unique<sf::Texture>(tex));
    }
}

Animation::Animation(double fps, const std::vector<std::string> & texNames) : fps(fps) {
    frames.resize(texNames.size());
    int i = 0;
    for (auto & name : texNames) {
        frames[i++]->loadFromFile(name);
    }
}

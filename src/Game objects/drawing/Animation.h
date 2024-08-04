//
// Created by livefish on 8/3/24.
//

#ifndef GAMEJAMPROG_ANIMATION_H
#define GAMEJAMPROG_ANIMATION_H

#include "Base.h"

class Animation {
public:
    Animation() = default;
    Animation(double fps, const std::string & spritesheetPath, int rows, int columns, int spriteCount);
    Animation(double fps, const std::vector<std::string> & texNames);
    Animation(double fps, const std::vector<sf::Texture> & textures);

    void update();

    static Animation getStaticAnimation(const sf::Texture & singleTexture);
    static Animation getStaticAnimation(const std::string & texPath);

    sf::Texture * curFrame();

private:
    void nextFrame();

private:
    sf::Clock clock;

    double fps = 0;
    std::size_t frame = 0;
    std::unique_ptr<sf::Image> spritesheet;
    std::vector<std::unique_ptr<sf::Texture>> frames;
};


#endif //GAMEJAMPROG_ANIMATION_H

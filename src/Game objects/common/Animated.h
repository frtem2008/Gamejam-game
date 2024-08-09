//
// Created by livefish on 8/9/24.
//

#ifndef GAMEJAMPROG_ANIMATED_H
#define GAMEJAMPROG_ANIMATED_H

class Animated {
public:
    Animated(const std::string & texPath, int fps, int rows, int columns, int frameCount) :
            animation(fps, texPath, rows, columns, frameCount) {
        animation.update();
    }

    sf::Texture * getAndNext() {
        animation.update();
        return animation.curFrame();
    }

    Animation animation;
};

#endif //GAMEJAMPROG_ANIMATED_H

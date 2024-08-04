//
// Created by livefish on 8/3/24.
//

#ifndef GAMEJAMPROG_MUSIC_PLAYER_H
#define GAMEJAMPROG_MUSIC_PLAYER_H

#include "Game object.h"

class MusicPlayer : public GameObject {
public:
    explicit MusicPlayer(const std::string & path, sf::Time gameLen, sf::Time offset)
            : GameObject(sf::Time::Zero, gameLen) {
        music.openFromFile(path);
        music.play();
        music.setPlayingOffset(offset);
    }

private:
    void tick(Window & win, gameObjectVec & gameObjects) override {
        if (!win.isActive) {
            music.pause();
            playing = false;
        }
        if (win.isActive && !playing) {
            music.play();
            playing = true;
        }
    }

    void draw(Window & win) override {
    }

private:
    sf::Music music;
    bool playing = true;
};

#endif //GAMEJAMPROG_MUSIC_PLAYER_H

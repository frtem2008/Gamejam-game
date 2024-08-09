//
// Created by livefish on 8/9/24.
//

#ifndef GAMEJAMPROG_ROUNDOBJECT_H
#define GAMEJAMPROG_ROUNDOBJECT_H

#include "Game object.h"

class RoundObject {
public:
    explicit RoundObject(sf::Sprite & sprite) : sprite(sprite) {}

    bool onScreen(Window & win) {
        auto view = win.win.getView();
        auto center = view.getCenter();
        auto size = view.getSize();

        return sprite.getGlobalBounds().intersects(
                sf::FloatRect(center - size / 2.f, size)
        );
    }

    float distance(sf::Vector2f pos2) {
        sf::Vector2f pos = sprite.getGlobalBounds().getPosition() + sprite.getOrigin() / 2.f;
        return sqrtf((pos.x - pos2.x) * (pos.x - pos2.x) + (pos.y - pos2.y) * (pos.y - pos2.y));
    }

    virtual float radius() {
        return std::max(sprite.getGlobalBounds().width, sprite.getGlobalBounds().height) / 2;
    }

    virtual ~RoundObject() = default;

private:
    sf::Sprite & sprite;
};

template<class ToCollide>
    requires std::is_base_of_v<RoundObject, ToCollide> && requires(ToCollide t) { t.sprite; }

    void onCollide(Window & win, sf::Sprite & sprite, std::unique_ptr<GameObject> & obj,
                   const std::function<void()> & action) {
        ToCollide * temp;

        if ((temp = dynamic_cast<ToCollide *>(obj.get()))) {
            auto bounds = sprite.getGlobalBounds();
            sf::Vector2f center = bounds.getPosition() + sprite.getOrigin() / 2.f;
            float radius = bounds.height / 2;

            if (temp->onScreen(win) && temp->distance(center) * 1.5 <= temp->radius() + radius) {
                action();
            }
        }
    }

template<class ToCollide>
    requires std::is_base_of_v<GameObject, ToCollide> && (!std::is_base_of_v<RoundObject, ToCollide>)
    void onCollide(Window & win, sf::Sprite & sprite, std::unique_ptr<GameObject> & obj,
                   const std::function<void()> & action) {
        ToCollide * temp;

        if ((temp = dynamic_cast<ToCollide *>(obj.get()))) {
            if (sprite.getGlobalBounds().intersects(temp->sprite.getGlobalBounds())) {
                action();
            }
        }
    }

#endif //GAMEJAMPROG_ROUNDOBJECT_H

//
// Created by Liam Ross on 27/03/2023.
//

#ifndef SPACE_INVADERS_ANIMATION_H
#define SPACE_INVADERS_ANIMATION_H

#include <SFML/Graphics.hpp>
#include <memory>

class Animation {
public:
    static constexpr const float TIMER_ZERO{0.f};
    static constexpr const float FRAME_DURATION{0.1f};

private:
    sf::Sprite& sprite;
    int rows;
    int cols;
    float timeElapsed;
    float frameDuration;
    int currentFrameIndex;

    bool loop;

public:
    Animation(sf::Sprite& spriteSheet, int rows, int cols, float frameDuration, bool loop) noexcept;

    void update(const float& dt);
    void render(std::shared_ptr<sf::RenderWindow> window);

    sf::Sprite getSprite();
    void setSpeed(float speed);
    float getSpeed() const;

    int getCurrentFrameIndex() const;

private:
    void setUpSprite();
};


#endif //SPACE_INVADERS_ANIMATION_H

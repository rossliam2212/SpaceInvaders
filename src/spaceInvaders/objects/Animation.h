//
// Created by Liam Ross on 27/03/2023.
//

#ifndef SPACE_INVADERS_ANIMATION_H
#define SPACE_INVADERS_ANIMATION_H

#include <SFML/Graphics.hpp>
#include <memory>

class Animation {
private:
    sf::Sprite& sprite;
    int rows;
    int cols;
    float timeElapsed;
    float frameDuration;
    int currentFrameIndex;

public:
    Animation(sf::Sprite& spriteSheet, int rows, int cols, float frameDuration) noexcept;

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

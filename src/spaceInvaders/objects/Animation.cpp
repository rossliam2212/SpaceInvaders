//
// Created by Liam Ross on 27/03/2023.
//

#include "Animation.h"

Animation::Animation(sf::Sprite& spriteSheet, int rows, int cols, float frameDuration, bool loop) noexcept
    : sprite{spriteSheet},
      rows{rows},
      cols{cols},
      timeElapsed{},
      frameDuration{frameDuration},
      currentFrameIndex{},
      loop{loop} {
    setUpSprite();
}

void Animation::update(const float& dt) {
    timeElapsed += dt;
    if (timeElapsed >= frameDuration) {
        currentFrameIndex = (currentFrameIndex + 1) % (rows * cols);
        int frameWidth = (int)sprite.getTexture()->getSize().x / cols;
        int frameHeight = (int)sprite.getTexture()->getSize().y / rows;
        int frameX = (currentFrameIndex % cols) * frameWidth;
        int frameY = (currentFrameIndex / cols) * frameHeight;
        sprite.setTextureRect(sf::IntRect(frameX, frameY, frameWidth, frameHeight));
        timeElapsed = 0;
    }
}

void Animation::render(std::shared_ptr<sf::RenderWindow> window) {
    window->draw(sprite);
}

sf::Sprite Animation::getSprite() {
    return sprite;
}

void Animation::setSpeed(float speed) {
    frameDuration = 1.f / speed;
}

float Animation::getSpeed() const {
    return 1.f / frameDuration;
}

int Animation::getCurrentFrameIndex() const {
    return currentFrameIndex;
}

void Animation::setUpSprite() {
    int x{(int)sprite.getTexture()->getSize().x};
    int frameWidth{x / cols};

    int y{(int)sprite.getTexture()->getSize().y};
    int frameHeight{y / rows};

    sprite.setTextureRect(sf::IntRect{0, 0, frameWidth, frameHeight});
}

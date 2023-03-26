//
// Created by Liam Ross on 27/03/2023.
//

#include "Animation.h"

Animation::Animation(const sf::Sprite& spriteSheet, int rows, int cols, int frameDuration) {

}

void Animation::update(const float& dt) {

}

void Animation::render(std::shared_ptr<sf::RenderWindow> window) {

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

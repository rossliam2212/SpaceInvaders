//
// Created by Liam Ross on 25/03/2023.
//

#include "Player.h"

Player::Player(const AssetManager& assetManager, const SoundManager& soundManager) noexcept
    : Character{PLAYER_NAME, sf::Vector2f{START_POSITION_X, START_POSITION_Y}, PLAYER_SPEED, assetManager, soundManager}{
    initSprite("playerShipGrayCenterSheet");
    initAnimations();
}

Player::Player(const sf::Vector2f& position, const AssetManager& assetManager, const SoundManager& soundManager) noexcept
    : Character{PLAYER_NAME, position, PLAYER_SPEED, assetManager, soundManager} {
    initSprite("playerShipGrayCenterSheet");
    initAnimations();

}

Player::Player(const std::string& name, const sf::Vector2f& position, float speed, const AssetManager& assetManager, const SoundManager& soundManager) noexcept
    : Character{name, position, speed, assetManager, soundManager} {
    initSprite("playerShipGrayCenterSheet");
    initAnimations();
}

void Player::update(const float& dt) {
    // TODO Dont loop over the animation map, check which direction player is moving and then change sprite
//    for (const auto& animation : animations) {
//        animation.second->update(dt);
//        sprite = animation.second->getSprite();
//    }

    if (!animations.empty()) {
        animations.at(still)->update(dt);
        sprite=animations.at(still)->getSprite();
    }

    position = sprite.getPosition();
    getInput(dt);
    checkForSpriteChange();
    move(dt, moveDirection.x);

}

void Player::render(std::shared_ptr<sf::RenderWindow> window) {
    window->draw(sprite);
}

void Player::getInput(const float& dt) {
    moveDirection.x = input::Input::KeyBoard::getAxis(dt, input::Input::KeyBoard::Axis::Horizontal);
}

void Player::checkForSpriteChange() {
    if (moveDirection.x < 0) {
        moveState = left;
    } else if (moveDirection.x > 0) {
        moveState = right;
    } else {
        moveState = still;
    }
}

void Player::initAnimations() {
    // TODO Make constants for Animation members - frame duration etc.
    // Center
    animations[still] = std::make_unique<Animation>(sprite, 1, 4, 0.1f);

}
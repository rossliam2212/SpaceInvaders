//
// Created by Liam Ross on 25/03/2023.
//

#include "Player.h"

Player::Player(const sf::Vector2f& position, const AssetManager& assetManager, const SoundManager& soundManager) noexcept
    : Character{PLAYER_NAME, position, PLAYER_SPEED, assetManager, soundManager} {
    initSprite("playerShipGrayCenter");
}

Player::Player(const std::string& name, const sf::Vector2f& position, float speed, const AssetManager& assetManager, const SoundManager& soundManager) noexcept
    : Character{name, position, speed, assetManager, soundManager} {
    initSprite("playerShipGrayCenter");
}

void Player::update(const float& dt) {
    position = sprite.getPosition();

    getInput(dt);
}

void Player::render(std::shared_ptr<sf::RenderWindow> window) {
    window->draw(sprite);
}

void Player::getInput(const float& dt) {
    moveDirection.x = input::Input::KeyBoard::getAxis(dt, input::Input::KeyBoard::Axis::Horizontal);

}
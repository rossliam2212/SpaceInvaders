//
// Created by Liam Ross on 28/03/2023.
//

#include "Enemy.h"

Enemy::Enemy(const std::string& name, const sf::Vector2f& position, const AssetManager& assetManager, const SoundManager& soundManager) noexcept
    : Character{name, position, DEFAULT_ENEMY_MOVE_SPEED, assetManager, soundManager} {

}

void Enemy::update(const float& dt) {

}

void Enemy::render(std::shared_ptr<sf::RenderWindow> window) {

}

void Enemy::shoot() {

}

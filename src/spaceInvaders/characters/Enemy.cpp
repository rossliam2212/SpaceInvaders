//
// Created by Liam Ross on 28/03/2023.
//

#include "Enemy.h"

Enemy::Enemy(const std::string& name, const sf::Vector2f& position, int scoreWorth, AssetManager& assetManager, SoundManager& soundManager) noexcept
    : Character{name, position, DEFAULT_ENEMY_MOVE_SPEED, assetManager, soundManager},
      weapon{assetManager, soundManager},
      scoreWorth{scoreWorth},
      isShooting{false},
      explosion{} {
}

void Enemy::update(const float& dt) {
    position = sprite.getPosition();
    weapon.update(dt);

    if (isDead()) {
        if (!drawExplosion) {
            drawExplosion = true;
        }
    }
}

void Enemy::render(std::shared_ptr<sf::RenderWindow> window) {
    window->draw(sprite);
    weapon.render(window);
}

void Enemy::moveX(const float& dt, float directionX) {
    auto delta{speed * dt};
    sprite.move(directionX * delta, DIRECTION_Y);
}

void Enemy::moveY(const float& dt, float directionY) {
    auto delta{speed * dt};
    sprite.move(DIRECTION_Y, directionY * delta);
}

void Enemy::shoot(const sf::Vector2f& shootPosition) {
    weapon.shoot(shootPosition);
}

int Enemy::getScoreWorth() const {
    return scoreWorth;
}

void Enemy::initSprite(const sf::Texture& texture) {
    sprite.setTexture(texture);
    sprite.setPosition(position);
    sprite.setScale(AssetManager::SPRITE_SCALE_UP_FACTOR, AssetManager::SPRITE_SCALE_UP_FACTOR);
}


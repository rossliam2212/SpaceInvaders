//
// Created by Liam Ross on 28/03/2023.
//

#include "Enemy.h"

Enemy::Enemy(const std::string& name, const sf::Vector2f& position, const AssetManager& assetManager, const SoundManager& soundManager) noexcept
    : Character{name, position, DEFAULT_ENEMY_MOVE_SPEED, assetManager, soundManager},
      isShooting{false},
      explosion{} {
//    initAnimation();
}

void Enemy::update(const float& dt) {
//    explosionAnimation->update(dt);
    if (isDead()) {
        if (!drawExplosion) {
            drawExplosion = true;
        }
    }
}

void Enemy::render(std::shared_ptr<sf::RenderWindow> window) {
        window->draw(sprite);
//        window->draw(explosion);
}

void Enemy::shoot() {

}

void Enemy::takeDamage(int damage) {
    Character::takeDamage(damage);
}

void Enemy::initSprite(const std::string& textureName) {
    sprite.setTexture(assetManager.getTexture(textureName));
    sprite.setPosition(position);
    sprite.setScale(AssetManager::SPRITE_SCALE_UP_FACTOR, AssetManager::SPRITE_SCALE_UP_FACTOR);
}

void Enemy::initAnimation() {
    explosion.setTexture(assetManager.getTexture("explosion"));
    explosion.setScale(AssetManager::SPRITE_SCALE_UP_FACTOR, AssetManager::SPRITE_SCALE_UP_FACTOR);
    explosionAnimation = std::make_unique<Animation>(explosion, 1, 3, Animation::FRAME_DURATION, false);
}

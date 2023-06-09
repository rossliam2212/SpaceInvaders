//
// Created by Liam Ross on 27/03/2023.
//

#include "Bullet.h"

Bullet::Bullet(int damage, int damageToAsteroid, const sf::Vector2f& spawnPosition, AssetManager& assetManager, SoundManager& soundManager) noexcept
    : spawnPosition{spawnPosition},
      damage{damage},
      damageToAsteroid{damageToAsteroid},
      alive{true},
      assetManager{assetManager},
      soundManager{soundManager} {
}

int Bullet::getDamage() const {
    return damage;
}

int Bullet::getDamageToAsteroid() const {
    return damageToAsteroid;
}

bool Bullet::isAlive() const {
    return alive;
}

void Bullet::setIsAlive(bool isAlive) {
    alive = isAlive;
}

sf::Vector2f Bullet::getPosition() const {
    return sprite.getPosition();
}

sf::FloatRect Bullet::getHitBox() const {
    return sprite.getGlobalBounds();
}

void Bullet::initSprite(const sf::Texture& texture) {
    sprite.setTexture(texture);
    sprite.setPosition(spawnPosition);
    sprite.setScale(AssetManager::SPRITE_SCALE_UP_FACTOR, AssetManager::SPRITE_SCALE_UP_FACTOR);
}

void Bullet::checkForBulletOffScreen() {
    sf::FloatRect bulletBounds{sprite.getGlobalBounds()};
    sf::FloatRect screenBounds{0, 0, WINDOW_WIDTH, WINDOW_HEIGHT};

    // If the bullet isn't within the screen bounds, then it is not alive
    if (!utilities::checkCollision(bulletBounds, screenBounds)) {
        alive = false;
    }
}

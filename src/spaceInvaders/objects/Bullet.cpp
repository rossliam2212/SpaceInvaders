//
// Created by Liam Ross on 27/03/2023.
//

#include "Bullet.h"

Bullet::Bullet(int damage, float lifeTime, const sf::Vector2f& spawnPosition, const AssetManager& assetManager,const SoundManager& soundManager) noexcept
    : spawnPosition{spawnPosition},
      damage{damage},
      lifeTime{lifeTime},
      timeAlive{},
      assetManager{assetManager},
      soundManager{soundManager} {
}

int Bullet::getDamage() const {
    return damage;
}

float Bullet::getLifeTime() const {
    return lifeTime;
}

float Bullet::getTimeAlive() const {
    return timeAlive;
}

bool Bullet::isAlive() const {
    return timeAlive < lifeTime;
}

void Bullet::initSprite(const std::string& textureName) {
    sprite.setTexture(assetManager.getTexture(textureName));
    sprite.setPosition(spawnPosition);
    sprite.setScale(AssetManager::SPRITE_SCALE_UP_FACTOR, AssetManager::SPRITE_SCALE_UP_FACTOR);
}

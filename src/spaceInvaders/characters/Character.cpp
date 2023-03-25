//
// Created by Liam Ross on 24/03/2023.
//

#include "Character.h"

Character::Character(const std::string& name, const sf::Vector2f& position, float speed, const AssetManager& assetManager, const SoundManager& soundManager) noexcept
    : Entity{name, position},
      assetManager{assetManager},
      soundManager{soundManager},
      health{MAX_HEALTH},
      speed{speed},
      dead{false} {
}

void Character::move(const float& dt, float directionX) {
    // Can only move along the x-axis
    float delta{speed * dt};
    sprite.move(directionX * delta, sprite.getPosition().y);
}

void Character::takeDamage(int damage) {
    health -= damage;

    if (health <= MIN_HEALTH) {
        kill();
    }
}

void Character::kill() {
    dead = true;
}

int Character::getHealth() const {
    return health;
}

float Character::getSpeed() const {
    return speed;
}

bool Character::isDead() const {
    return dead;
}

void Character::initSprite(const sf::Texture& texture) {
    // TODO Set sprite texture from asset manager
    // Set sprite position
    // Center the origin of the sprite
}

void Character::initSprite(const std::string& textureName) {
    auto size{assetManager.getTexture(textureName).getSize()};
    sprite.setTexture(assetManager.getTexture(textureName));
    sprite.setOrigin((float)size.x/2 ,(float)size.y/2);
    sprite.setPosition(position);
    sprite.setScale(10, 10);
}
//
// Created by Liam Ross on 24/03/2023.
//

#include "Character.h"

Character::Character(const std::string& name, const sf::Vector2f& position, float speed, AssetManager& assetManager, SoundManager& soundManager) noexcept
    : Entity{name, position},
      assetManager{assetManager},
      soundManager{soundManager},
      health{MAX_HEALTH},
      speed{speed},
      dead{false} {
}

void Character::move(const float& dt, float directionX) {
    // Can only move along the x-axis
    float delta{speed * dt * SPEED_MULTIPLIER};
    sprite.move(directionX * delta, DIRECTION_Y);
}

void Character::move(const float& dt, sf::Sprite& s, float directionX) {
    float delta{speed * dt * SPEED_MULTIPLIER};
    s.move(directionX * delta, DIRECTION_Y);
}


void Character::increaseHealth(int healthIncrease) {
    if ((health + healthIncrease) > MAX_HEALTH) {
        health = MAX_HEALTH;
    } else {
        health += healthIncrease;
    }
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

int Character::getMaxHealth() {
    return MAX_HEALTH;
}

float Character::getSpeed() const {
    return speed;
}

bool Character::isDead() const {
    return dead;
}

sf::FloatRect Character::getHitBox() const {
    return sprite.getGlobalBounds();
}

sf::Vector2u Character::getSize() const {
    return sprite.getTexture()->getSize();
}
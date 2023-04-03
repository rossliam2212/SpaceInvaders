//
// Created by Liam Ross on 02/04/2023.
//

#include "Asteroid.h"

Asteroid::Asteroid(const sf::Vector2f& position, AssetManager& assetManager, SoundManager& soundManager) noexcept
    : Entity{ASTEROID_NAME, position},
      health{ASTEROID_MAX_HEALTH},
      dead{false},
      sprite{assetManager.getTexture("bigAsteroid")},
      assetManager{assetManager},
      soundManager{soundManager} {
    initText();
    initSprite();
}

void Asteroid::update(const float& dt) {
    position = sprite.getPosition();
    healthText.setString(std::to_string(health));
}

void Asteroid::render(std::shared_ptr<sf::RenderWindow> window) {
    window->draw(sprite);
    window->draw(healthText);
}

void Asteroid::takeDamage(int damage) {
    health -= damage;

    if (health <= 0) {
        dead = true;
    }
}

int Asteroid::getHealth() const {
    return health;
}

int Asteroid::getMaxHealth() {
    return ASTEROID_MAX_HEALTH;
}

sf::FloatRect Asteroid::getHitBox() const {
    return sprite.getGlobalBounds();
}

bool Asteroid::isDead() const {
    return dead;
}

void Asteroid::initText() {
    healthText.setFont(assetManager.getFont("PixelFont"));
    healthText.setCharacterSize(AssetManager::FONT_PARAGRAPH);
    healthText.setFillColor(assetManager.getColor("white"));
    healthText.setString(std::to_string(health));

    healthText.setPosition(position.x - 25.f, position.y - 30.f);
}

void Asteroid::initSprite() {
    sprite.setScale(AssetManager::SPRITE_SCALE_UP_FACTOR * 1.5f, AssetManager::SPRITE_SCALE_UP_FACTOR * 1.5f);
    sprite.setOrigin(sprite.getTexture()->getSize().x / 2.f, sprite.getTexture()->getSize().y / 2.f);
    sprite.setPosition(position);
}
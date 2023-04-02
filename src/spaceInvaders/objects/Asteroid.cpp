//
// Created by Liam Ross on 02/04/2023.
//

#include "Asteroid.h"

Asteroid::Asteroid(const sf::Vector2f& position, AssetManager& assetManager, SoundManager& soundManager) noexcept
    : Entity{ASTEROID_NAME, position},
      health{ASTEROID_MAX_HEALTH},
      explosionAnimation{explosion, 1, 3, Animation::FRAME_DURATION, false},
      assetManager{assetManager},
      soundManager{soundManager} {
    initText();
    initSprite();
}

void Asteroid::update(const float& dt) {

}

void Asteroid::render(std::shared_ptr<sf::RenderWindow> window) {
    window->draw(sprite);
}

void Asteroid::initText() {

}

void Asteroid::initSprite() {
    sprite.setTexture(assetManager.getTexture("bigAsteroid"));
    sprite.setScale(AssetManager::SPRITE_SCALE_UP_FACTOR, AssetManager::SPRITE_SCALE_UP_FACTOR);
    sprite.setPosition(position);

    explosion.setScale(AssetManager::SPRITE_SCALE_UP_FACTOR + 5.f, AssetManager::SPRITE_SCALE_UP_FACTOR + 5.f);
}
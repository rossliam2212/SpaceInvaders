//
// Created by Liam Ross on 01/04/2023.
//

#include "HealthPowerUp.h"

HealthPowerUp::HealthPowerUp(const sf::Vector2f& position, AssetManager& assetManager, SoundManager& soundManager) noexcept
        : PowerUp{position, assetManager, soundManager} {
    initSprite(assetManager.getTexture("healthPowerUp"));
}

void HealthPowerUp::update(const float& dt) { }

void HealthPowerUp::render(std::shared_ptr<sf::RenderWindow> window) {
    window->draw(sprite);
}
//
// Created by Liam Ross on 01/04/2023.
//

#include "ShieldPowerUp.h"

ShieldPowerUp::ShieldPowerUp(const sf::Vector2f& position, AssetManager& assetManager, SoundManager& soundManager) noexcept
    : PowerUp{position, assetManager, soundManager} {
    initSprite(assetManager.getTexture("shieldPowerUp"));
}

void ShieldPowerUp::update(const float& dt) { }

void ShieldPowerUp::render(std::shared_ptr<sf::RenderWindow> window) {
    window->draw(sprite);
}

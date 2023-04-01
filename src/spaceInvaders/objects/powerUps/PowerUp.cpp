//
// Created by Liam Ross on 01/04/2023.
//

#include "PowerUp.h"

PowerUp::PowerUp(const sf::Vector2f& position, AssetManager& assetManager, SoundManager& soundManager) noexcept
    : position{position},
      assetManager{assetManager},
      soundManager{soundManager},
      isUsed{false} {
}

void PowerUp::setIsUsed(bool used) {
    isUsed = used;
}

bool PowerUp::getIsUsed() const {
    return isUsed;
}

void PowerUp::initSprite(const sf::Texture& texture) {
    sprite.setPosition(position);
    sprite.setTexture(texture);
    sprite.setScale(AssetManager::SPRITE_SCALE_UP_FACTOR, AssetManager::SPRITE_SCALE_UP_FACTOR);
}
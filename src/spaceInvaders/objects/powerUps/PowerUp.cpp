//
// Created by Liam Ross on 01/04/2023.
//

#include "PowerUp.h"

PowerUp::PowerUp(const std::string& name, const sf::Vector2f& position, AssetManager& assetManager, SoundManager& soundManager) noexcept
    : Entity{name, position},
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

sf::FloatRect PowerUp::getHitBox() const {
    return sprite.getGlobalBounds();
}

void PowerUp::initSprite(const sf::Texture& texture) {
    sprite.setPosition(position);
    sprite.setTexture(texture);
    sprite.setScale(AssetManager::SPRITE_SCALE_UP_FACTOR/2.f, AssetManager::SPRITE_SCALE_UP_FACTOR/2.f);
}
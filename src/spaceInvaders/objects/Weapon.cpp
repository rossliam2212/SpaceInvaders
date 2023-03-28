//
// Created by Liam Ross on 27/03/2023.
//

#include "Weapon.h"

Weapon::Weapon(float fireRate, const sf::Vector2f& shootPosition, const AssetManager& assetManager, const SoundManager& soundManager) noexcept
    : fireRate{fireRate},
      shootPosition{shootPosition},
      timeSinceLastShot{},
      assetManager{assetManager},
      soundManager{soundManager} {
}

float Weapon::getFireRate() const {
    return fireRate;
}

sf::Vector2f Weapon::getShootPosition() const {
    return shootPosition;
}

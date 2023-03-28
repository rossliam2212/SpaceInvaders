//
// Created by Liam Ross on 27/03/2023.
//

#include "Weapon.h"

Weapon::Weapon(float bulletSpeed, float fireRate, const sf::Vector2f& shootPosition, const AssetManager& assetManager, const SoundManager& soundManager) noexcept
    : bulletSpeed{bulletSpeed},
      fireRate{fireRate},
      shootPosition{shootPosition},
      timeSinceLastShot{},
      assetManager{assetManager},
      soundManager{soundManager} {
}

//void Weapon::shoot() {
//    if (timeSinceLastShot >= 1.f / fireRate) {
//
//        fireRate = 0.f;
//    }
//}

float Weapon::getBulletSpeed() const {
    return bulletSpeed;
}

float Weapon::getFireRate() const {
    return fireRate;
}

sf::Vector2f Weapon::getShootPosition() const {
    return shootPosition;
}

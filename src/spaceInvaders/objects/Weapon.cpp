//
// Created by Liam Ross on 27/03/2023.
//

#include "Weapon.h"

Weapon::Weapon(int damage, float bulletSpeed, float fireRate, const sf::Vector2f& shootPosition) noexcept
    : damage{damage},
      bulletSpeed{bulletSpeed},
      fireRate{fireRate},
      shootPosition{shootPosition},
      timeSinceLastShot{} {
}

void Weapon::update(const float& dt) {

}

void Weapon::render(std::shared_ptr<sf::RenderWindow> window) {

}

void Weapon::shoot() {
    if (timeSinceLastShot >= 1.f / fireRate) {

        fireRate = 0.f;
    }
}


int Weapon::getDamage() const {
    return damage;
}

float Weapon::getBulletSpeed() const {
    return bulletSpeed;
}

float Weapon::getFireRate() const {
    return fireRate;
}

sf::Vector2f Weapon::getShootPosition() const {
    return shootPosition;
}

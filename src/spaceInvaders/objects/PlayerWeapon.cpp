//
// Created by Liam Ross on 28/03/2023.
//

#include "PlayerWeapon.h"

PlayerWeapon::PlayerWeapon(float fireRate, const sf::Vector2f& shootPosition, const AssetManager& assetManager, const SoundManager& soundManager) noexcept
    : Weapon{PLAYER_WEAPON_BULLET_SPEED, PLAYER_WEAPON_FIRE_RATE, shootPosition, assetManager, soundManager} {
}

void PlayerWeapon::update(const float& dt) {
    for (const auto& bullet : bullets) {
        bullet->update(dt);
    }
}

void PlayerWeapon::render(std::shared_ptr<sf::RenderWindow> window) {
    for (const auto& bullet : bullets) {
        bullet->render(window);
    }
}

void PlayerWeapon::shoot() {
    // TODO Add shoot sound
    if (timeSinceLastShot >= 1.f / fireRate) {
        bullets.emplace_back(std::make_unique<PlayerBullet>(shootPosition, assetManager, soundManager));
        fireRate = 0.f;
    }

    // TODO Add ability to shoot rockets
}

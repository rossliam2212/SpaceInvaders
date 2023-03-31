//
// Created by Liam Ross on 28/03/2023.
//

#include "PlayerWeapon.h"

PlayerWeapon::PlayerWeapon(AssetManager& assetManager, SoundManager& soundManager) noexcept
    : Weapon{PLAYER_WEAPON_SHOOT_COOL_DOWN, assetManager, soundManager} {
}

void PlayerWeapon::update(const float& dt) {
    cleanUpBullets();

    if (shootCoolDownTimer) {
        shootCoolDown -= dt;
        if (shootCoolDown <= 0.f) {
            isShooting = false;
            shootCoolDownTimer = false;
            shootCoolDown = PLAYER_WEAPON_SHOOT_COOL_DOWN;
            soundManager.stopSound("playerShootingBulletSound");
        }
    }

    for (const auto& bullet : bullets) {
        if (bullet->isAlive()) {
            bullet->update(dt);
        }
    }
}

void PlayerWeapon::render(std::shared_ptr<sf::RenderWindow> window) {
    for (const auto& bullet : bullets) {
        if (bullet->isAlive()) {
            bullet->render(window);
        }
    }
}

void PlayerWeapon::shoot(const sf::Vector2f& shootPosition) {
    // TODO Add ability to shoot rockets

    if (!isShooting) {
        isShooting = true;

        soundManager.startSound("playerShootingBulletSound", assetManager.getSound("playerShootingBulletSound"));

        bullets.emplace_back(std::make_unique<PlayerBullet>(shootPosition, assetManager, soundManager));
        shootCoolDownTimer = true;
    }
}

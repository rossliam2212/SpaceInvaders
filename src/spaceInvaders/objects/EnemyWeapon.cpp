//
// Created by Liam Ross on 31/03/2023.
//

#include "EnemyWeapon.h"

EnemyWeapon::EnemyWeapon(const AssetManager& assetManager, const SoundManager& soundManager) noexcept
    : Weapon{ENEMY_WEAPON_SHOOT_COOL_DOWN, assetManager, soundManager} {
}

void EnemyWeapon::update(const float& dt) {
    cleanUpBullets();

    if (shootCoolDownTimer) {
        shootCoolDown -= dt;
        if (shootCoolDown <= 0.f) {
            isShooting = false;
            shootCoolDownTimer = false;
            shootCoolDown = ENEMY_WEAPON_SHOOT_COOL_DOWN;

            // Stop the shooting sound
            soundManager.stopSound("enemyShootingBulletSound");
        }
    }

    for (const auto& bullet : bullets) {
        if (bullet->isAlive()) {
            bullet->update(dt);
        }
    }
}

void EnemyWeapon::render(std::shared_ptr<sf::RenderWindow> window) {
    for (const auto& bullet : bullets) {
        if (bullet->isAlive()) {
            bullet->render(window);
        }
    }
}

void EnemyWeapon::shoot(const sf::Vector2f& shootPosition) {
    if (!isShooting) {
        isShooting = true;

        // Play Sound
        soundManager.startSound("enemyShootingBulletSound", assetManager.getSound("enemyShootingBulletSound"));

        // Create instance of bullet
        bullets.emplace_back(std::make_unique<EnemyBullet>(shootPosition, assetManager, soundManager));

        shootCoolDownTimer = true;
    }
}
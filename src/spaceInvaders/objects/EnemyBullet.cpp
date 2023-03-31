//
// Created by Liam Ross on 31/03/2023.
//

#include "EnemyBullet.h"

EnemyBullet::EnemyBullet(const sf::Vector2f& spawnPosition, const AssetManager& assetManager, const SoundManager& soundManager) noexcept
    : Bullet{ENEMY_BULLET_DAMAGE, spawnPosition, assetManager, soundManager} {
    initSprite("enemyBullet");
}

void EnemyBullet::update(const float& dt) {
    float delta{ENEMY_BULLET_SPEED * dt * ENEMY_BULLET_SPEED_MULTIPLIER};
    sprite.move(0, delta);
}

void EnemyBullet::render(std::shared_ptr<sf::RenderWindow> window) {
    window->draw(sprite);
}
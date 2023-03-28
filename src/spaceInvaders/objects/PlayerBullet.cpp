//
// Created by Liam Ross on 28/03/2023.
//

#include "PlayerBullet.h"

PlayerBullet::PlayerBullet(const sf::Vector2f& spawnPosition, const AssetManager& assetManager, const SoundManager& soundManager) noexcept
    : Bullet{PLAYER_BULLET_DAMAGE, spawnPosition, assetManager, soundManager} {
    initSprite("playerBullet");
}

void PlayerBullet::update(const float& dt) {
    // Player bullets only shoot upwards
    float delta{PLAYER_BULLET_SPEED * dt * PLAYER_BULLET_SPEED_MULTIPLIER};
    sprite.move(0, -delta);

    checkForBulletOffScreen();
}

void PlayerBullet::render(std::shared_ptr<sf::RenderWindow> window) {
    window->draw(sprite);
}
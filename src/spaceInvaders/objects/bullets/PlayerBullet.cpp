//
// Created by Liam Ross on 28/03/2023.
//

#include "PlayerBullet.h"

PlayerBullet::PlayerBullet(const sf::Vector2f& spawnPosition, AssetManager& assetManager, SoundManager& soundManager) noexcept
    : Bullet{PLAYER_BULLET_DAMAGE, PLAYER_BULLET_DAMAGE_ASTEROID, spawnPosition, assetManager, soundManager} {
    initSprite(assetManager.getTexture("playerBullet"));
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
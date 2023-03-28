//
// Created by Liam Ross on 28/03/2023.
//

#include "PlayerBullet.h"

PlayerBullet::PlayerBullet(const sf::Vector2f& spawnPosition, const AssetManager& assetManager, const SoundManager& soundManager) noexcept
    : Bullet{PLAYER_BULLET_DAMAGE, PLAYER_BULLET_LIFE_TIME, spawnPosition, assetManager, soundManager} {
    initSprite("playerBullet");
}

void PlayerBullet::update(const float& dt) {
    // TODO Move the bullet
//    sprite.move();
    timeAlive += dt;
}

void PlayerBullet::render(std::shared_ptr<sf::RenderWindow> window) {

}
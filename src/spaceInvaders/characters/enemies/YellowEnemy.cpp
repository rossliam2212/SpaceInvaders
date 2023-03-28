//
// Created by Liam Ross on 28/03/2023.
//

#include "YellowEnemy.h"

YellowEnemy::YellowEnemy(const sf::Vector2f& position, const AssetManager& assetManager, const SoundManager& soundManager) noexcept
    : Enemy{YELLOW_ENEMY_NAME, position, assetManager, soundManager} {
    initSprite("yellowEnemyShip");
}
//
// Created by Liam Ross on 28/03/2023.
//

#include "PurpleEnemy.h"

PurpleEnemy::PurpleEnemy(const sf::Vector2f& position, const AssetManager& assetManager, const SoundManager& soundManager) noexcept
        : Enemy{PURPLE_ENEMY_NAME, position, PURPLE_ENEMY_SCORE_WORTH, assetManager, soundManager} {
    initSprite("purpleEnemyShip");
}
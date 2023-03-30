//
// Created by Liam Ross on 28/03/2023.
//

#include "GreenEnemy.h"

GreenEnemy::GreenEnemy(const sf::Vector2f& position, const AssetManager& assetManager, const SoundManager& soundManager) noexcept
        : Enemy{GREEN_ENEMY_NAME, position, GREEN_ENEMY_SCORE_WORTH, assetManager, soundManager} {
    initSprite("greenEnemyShip");
}
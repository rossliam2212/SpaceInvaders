//
// Created by Liam Ross on 28/03/2023.
//

#include "BlueEnemy.h"

BlueEnemy::BlueEnemy(const sf::Vector2f& position, const AssetManager& assetManager, const SoundManager& soundManager) noexcept
    : Enemy{BLUE_ENEMY_NAME, position, BLUE_ENEMY_SCORE_WORTH, assetManager, soundManager} {
    initSprite("blueEnemyShip");
}

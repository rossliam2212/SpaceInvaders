//
// Created by Liam Ross on 28/03/2023.
//

#include "YellowEnemy.h"

YellowEnemy::YellowEnemy(const sf::Vector2f& position, AssetManager& assetManager, SoundManager& soundManager) noexcept
    : Enemy{YELLOW_ENEMY_NAME, position, YELLOW_ENEMY_SCORE_WORTH, assetManager, soundManager} {
    initSprite(assetManager.getTexture("yellowEnemyShip"));
}
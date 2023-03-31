//
// Created by Liam Ross on 31/03/2023.
//

#include "EnemyFactory.h"

std::unique_ptr<Enemy> EnemyFactory::createEnemy(const std::string& enemyType, const sf::Vector2f& position, AssetManager& assetManager, SoundManager& soundManager) {
    if (enemyType == "Blue") {
        return std::make_unique<BlueEnemy>(position, assetManager, soundManager);
    } else if (enemyType == "Yellow") {
        return std::make_unique<YellowEnemy>(position, assetManager, soundManager);
    } else if (enemyType == "Green") {
        return std::make_unique<GreenEnemy>(position, assetManager, soundManager);
    } else if (enemyType == "Purple") {
        return std::make_unique<PurpleEnemy>(position, assetManager, soundManager);
    } else {
        return nullptr;
    }
}

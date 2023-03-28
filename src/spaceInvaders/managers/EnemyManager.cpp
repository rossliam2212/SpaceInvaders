//
// Created by Liam Ross on 28/03/2023.
//

#include "EnemyManager.h"

EnemyManager::EnemyManager(Player* player, const AssetManager& assetManager, const SoundManager& soundManager) noexcept
    : player{player},
      assetManager{assetManager},
      soundManager{soundManager},
      logger{"logs"},
      numberOfBlueEnemies{},
      numberOfGreenEnemies{},
      numberOfYellowEnemies{},
      numberOfPurpleEnemies{} {
    initEnemies();
}

void EnemyManager::update(const float& dt) {
    checkCollisions();

    for (const auto& enemy : enemies) {
        if (!enemy->isDead()) {
            enemy->update(dt);
        }
    }
}

void EnemyManager::render(std::shared_ptr<sf::RenderWindow> window) {
    for (const auto& enemy : enemies) {
        if (!enemy->isDead()) {
            enemy->render(window);
        }
    }
}

void EnemyManager::checkCollisions() {
    // Get player bullet sprite
    // Get enemy sprite
    // Check if their boundaries intersect
}

void EnemyManager::initEnemies() {
    float x = START_POSITION_X;
    float y = START_POSITION_Y;

    for (auto i = 0; i < MAX_NUMBER_OF_BLUE_ENEMIES; ++i) {
        enemies.emplace_back(std::make_unique<BlueEnemy>(sf::Vector2f{x, y}, assetManager, soundManager));
        x += START_POSITION_X;
        numberOfBlueEnemies++;
    }
    logger.info("Blue enemies initialized.", this);
}


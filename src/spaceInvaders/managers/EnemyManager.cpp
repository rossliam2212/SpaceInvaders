//
// Created by Liam Ross on 28/03/2023.
//

#include "EnemyManager.h"

EnemyManager::EnemyManager(const AssetManager& assetManager, const SoundManager& soundManager) noexcept
    : assetManager{assetManager},
      soundManager{soundManager},
      logger{"logs"} {
    initEnemies();
}

void EnemyManager::update(const float& dt) {
    for (const auto& enemy : enemies) {
        enemy->update(dt);
    }
}

void EnemyManager::render(std::shared_ptr<sf::RenderWindow> window) {
    for (const auto& enemy : enemies) {
        enemy->render(window);
    }
}

void EnemyManager::initEnemies() {
    enemies.emplace_back(std::make_unique<BlueEnemy>(sf::Vector2f{100, 100}, assetManager, soundManager));
    logger.info("Enemies initialized.", this);
}


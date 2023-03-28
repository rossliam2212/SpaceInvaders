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
    cleanUpEnemies();
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
    auto playerBullets{player->getWeapon()->getBullets()};

    for (auto& enemy : enemies) {
        sf::FloatRect enemyHitBox{enemy->getHitBox()};

        for (auto& bullet : playerBullets) {
            if (!bullet->isAlive()) {
                continue;
            }

            sf::FloatRect bulletHitBox{bullet->getHitBox()};

            if (utilities::checkCollision(bulletHitBox, enemyHitBox)) {
                bullet->setIsAlive(false);
                enemy->takeDamage(bullet->getDamage());
                logger.debug("ENEMY HIT => " + enemy->getName() + ".", this);
            }
        }
    }
}

void EnemyManager::cleanUpEnemies() {
    enemies.erase(std::remove_if(std::begin(enemies), std::end(enemies), [](const auto& e) {
        return e->isDead();
    }), std::end(enemies));
}

void EnemyManager::initEnemies() {
    // Purple Enemies
    float x = START_POSITION_X;
    float y = START_POSITION_Y;

    for (auto i = 0; i < MAX_NUMBER_OF_PURPLE_ENEMIES; ++i) {
        enemies.emplace_back(std::make_unique<PurpleEnemy>(sf::Vector2f{x, y}, assetManager, soundManager));
        x += GAP_BETWEEN_ENEMIES_X;
        numberOfBlueEnemies++;
    }
    logger.info("Purple enemies initialized.", this);

    // Green Enemies
    x = START_POSITION_X;
    y += GAP_BETWEEN_ENEMIES_Y;

    for (auto i = 0; i < MAX_NUMBER_OF_GREEN_ENEMIES; ++i) {
        enemies.emplace_back(std::make_unique<GreenEnemy>(sf::Vector2f{x, y}, assetManager, soundManager));
        x += GAP_BETWEEN_ENEMIES_X;
        numberOfGreenEnemies++;
    }
    logger.info("Purple enemies initialized.", this);

    // Yellow Enemies
    x = START_POSITION_X;
    y += GAP_BETWEEN_ENEMIES_Y;

    for (auto i = 0; i < MAX_NUMBER_OF_YELLOW_ENEMIES; ++i) {
        enemies.emplace_back(std::make_unique<YellowEnemy>(sf::Vector2f{x, y}, assetManager, soundManager));
        x += GAP_BETWEEN_ENEMIES_X;
        numberOfYellowEnemies++;
    }
    logger.info("Yellow enemies initialized.", this);

    // Blue Enemies
    x = START_POSITION_X;
    y += GAP_BETWEEN_ENEMIES_Y;

    for (auto i = 0; i < MAX_NUMBER_OF_BLUE_ENEMIES; ++i) {
        enemies.emplace_back(std::make_unique<BlueEnemy>(sf::Vector2f{x, y}, assetManager, soundManager));
        x += GAP_BETWEEN_ENEMIES_X;
        numberOfPurpleEnemies++;
    }
    logger.info("Blue enemies initialized.", this);
}


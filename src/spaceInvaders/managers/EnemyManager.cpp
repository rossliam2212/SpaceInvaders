//
// Created by Liam Ross on 28/03/2023.
//

#include "EnemyManager.h"

const std::vector<std::tuple<std::string, int>> EnemyManager::data {
        {"Purple", MAX_NUMBER_OF_PURPLE_ENEMIES},
        {"Green", MAX_NUMBER_OF_GREEN_ENEMIES},
        {"Yellow", MAX_NUMBER_OF_YELLOW_ENEMIES},
        {"Blue", MAX_NUMBER_OF_BLUE_ENEMIES}
};

EnemyManager::EnemyManager(Player* player, AssetManager& assetManager, SoundManager& soundManager) noexcept
    : player{player},
      direction{moveRight},
      assetManager{assetManager},
      soundManager{soundManager},
      logger{"logs"},
      explosion{assetManager.getTexture("explosion")},
      explosionAnimation{explosion, 1, 3, Animation::FRAME_DURATION, false},
      explosionPlaying{false},
      explosionTimer{false},
      explosionCoolDown{EXPLOSION_COOL_DOWN_TIMER},
      shooting{false},
      shootingTimer{false},
      shootCoolDown{SHOOT_COOL_DOWN_TIMER} {
    initEnemies();

    explosion.setScale(AssetManager::SPRITE_SCALE_UP_FACTOR + 5.f, AssetManager::SPRITE_SCALE_UP_FACTOR + 5.f);
}

void EnemyManager::update(const float& dt) {
    moveEnemiesX(dt);
    cleanUpEnemies();
    checkCollisions();
    shoot();

    direction = getDirection(dt);

    // Only update the animation when an enemy is killed
    if (explosionPlaying) {
        explosionAnimation.update(dt);
    }

    // Displays the explosion animation for a certain amount of time.
    if (explosionTimer) {
        explosionCoolDown -= dt;
        if (explosionCoolDown <= TIMER_ZERO) {
            explosionPlaying = false;
            explosionTimer = false;
            explosionCoolDown = EXPLOSION_COOL_DOWN_TIMER;

            soundManager.stopSound("explosionSound");
        }
    }

    if (shootingTimer) {
        shootCoolDown -= dt;
        if (shootCoolDown <= TIMER_ZERO) {
            shooting = false;
            shootingTimer = false;
            shootCoolDown = SHOOT_COOL_DOWN_TIMER;
        }
    }

    if (!allEnemiesDead()) {
        for (const auto& enemy: enemies) {
            if (!enemy->isDead()) {
                enemy->update(dt);
            } else {
                // If the enemy is dead, then play the explosion animation at the dead enemies position
                explosionPlaying = true;
                createExplosion(enemy->getPosition());
            }
        }
    }
}

void EnemyManager::render(std::shared_ptr<sf::RenderWindow> window) {
    if (explosionPlaying) {
        window->draw(explosion);
    }

    if (!allEnemiesDead()) {
        for (const auto& enemy: enemies) {
            if (!enemy->isDead()) {
                enemy->render(window);
            }
        }
    }
}

void EnemyManager::moveEnemiesX(const float& dt) {
    if (!allEnemiesDead()) {
        for (const auto& enemy : enemies) {
            if (!enemy->isDead()) {
                if (direction == moveRight) {
                    enemy->moveX(dt, ENEMY_MOVE_X_SPEED);
                } else if (direction == moveLeft) {
                    enemy->moveX(dt, -ENEMY_MOVE_X_SPEED);
                }
            }
        }
    }
}

// TODO Not Working - FIX
void EnemyManager::moveEnemiesY(const float& dt) {
    if (!allEnemiesDead()) {
        for (const auto& enemy: enemies) {
//        sf::Vector2f pos{enemy->getPosition()};
//        sf::Vector2f newPos{sf::Vector2f{pos.x, pos.y + 20.f}};
//        enemy->setPosition(newPos);
            enemy->moveY(dt, ENEMY_MOVE_Y_SPEED);
        }
    }
}

void EnemyManager::shoot() {
    if (!allEnemiesDead()) {
        if (!shooting) {
            shooting = true;
            int randomEnemy{utilities::randomInt(0, (int) enemies.size() - 1)};
            enemies.at(randomEnemy)->shoot(enemies.at(randomEnemy)->getPosition());

            shootingTimer = true;
        }
    }
}

MoveDirection EnemyManager::getDirection(const float& dt) {
    if (!allEnemiesDead()) {
        for (const auto& enemy: enemies) {
            // TODO Fix this so the enemies don't go off screen
            sf::FloatRect enemyBounds{enemy->getHitBox()};
            sf::FloatRect screenBounds{0, 0, static_cast<float>(1500 - enemy->getSize().x), 1500};

            if (!utilities::checkCollision(enemyBounds, screenBounds)) {
                if (direction == moveRight) {
                    moveEnemiesY(dt);
                    return moveLeft;
                } else {
                    moveEnemiesY(dt);
                    return moveRight;
                }
            }
        }
    }
    return direction;
}

void EnemyManager::createExplosion(const sf::Vector2f& position) {
    explosion.setPosition(position);
    explosionTimer = true;

    soundManager.startSound("explosionSound", assetManager.getSound("explosionSound"));
}

void EnemyManager::checkCollisions() {
    // Get player bullet sprite
    // Get enemy sprite
    // Check if their boundaries intersect

    if (!allEnemiesDead() && player != nullptr) {
        auto playerBullets{player->getWeapon()->getBullets()};

        for (const auto& enemy : enemies) {
            sf::FloatRect enemyHitBox{enemy->getHitBox()};

            for (const auto& bullet : playerBullets) {
                if (!bullet->isAlive()) {
                    continue;
                }

                sf::FloatRect bulletHitBox{bullet->getHitBox()};

                if (utilities::checkCollision(bulletHitBox, enemyHitBox)) {
                    bullet->setIsAlive(false); // Kill the bullet
                    enemy->takeDamage(bullet->getDamage()); // Deal damage to the enemy
                    player->increaseScore(enemy->getScoreWorth()); // Increase the players score
                    player->updateKillStats(enemy->getName()); // Update the players kill stats
                    logger.debug("ENEMY HIT => " + enemy->getName() + ".", this);
                }
            }
        }
    }
}

bool EnemyManager::allEnemiesDead() {
    return enemies.empty();
}

void EnemyManager::cleanUpEnemies() {
    // If an enemy is dead, then they are removed from the enemies vector
    enemies.erase(std::remove_if(std::begin(enemies), std::end(enemies), [](const auto& e) {
        return e->isDead();
    }), std::end(enemies));
}

void EnemyManager::initEnemies() {
    // TODO Make this more efficient

    // Testing execution time
    auto startTime{std::chrono::steady_clock::now()};
    enemies.reserve(MAX_NUMBER_OF_BLUE_ENEMIES +
                    MAX_NUMBER_OF_GREEN_ENEMIES +
                    MAX_NUMBER_OF_YELLOW_ENEMIES +
                    MAX_NUMBER_OF_PURPLE_ENEMIES);

    float x;
    float y{ENEMY_START_POSITION_Y};

    for (const auto& [name, number] : data) {
        x = ENEMY_START_POSITION_X;
        for (auto i = 0; i < number; ++i) {
            enemies.emplace_back(enemyFactory.createEnemy(name, sf::Vector2f{x, y}, assetManager, soundManager));
            x += GAP_BETWEEN_ENEMIES_X;
        }
        y += GAP_BETWEEN_ENEMIES_Y;
        logger.info(name + " enemies initialized", this);
    }
    auto endTime = std::chrono::steady_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime);
    logger.timing("initEnemies", duration.count(), this);
}



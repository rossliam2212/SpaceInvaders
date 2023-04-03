//
// Created by Liam Ross on 01/04/2023.
//

#include "ObjectManager.h"

ObjectManager::ObjectManager(Player* player, EnemyManager* enemyManager, AssetManager& assetManager, SoundManager& soundManager) noexcept
    : player{player},
      enemyManager{enemyManager},
      assetManager{assetManager},
      soundManager{soundManager},
      logger{"logs"} {
    createPowerUp();
    initAsteroids();
}

void ObjectManager::update(const float& dt) {
    checkPowerUpCollisions();
    cleanUpPowerUps();
    checkAsteroidCollisions();
    cleanUpAsteroids();

    if (!allPowerUpsDead()) {
        for (const auto& powerUp : powerUps) {
            if (!powerUp->getIsUsed()) {
                powerUp->update(dt);
            }
        }
    }

    if (!asteroids.empty()) {
        for (auto& asteroid : asteroids) {
            if (!asteroid->isDead()) {
                asteroid->update(dt);
            }
        }
    }
}

void ObjectManager::render(std::shared_ptr<sf::RenderWindow> window) {
    if (!allPowerUpsDead()) {
        for (const auto& powerUp : powerUps) {
            if (!powerUp->getIsUsed()) {
                powerUp->render(window);
            }
        }
    }

    if (!asteroids.empty()) {
        for (auto& asteroid : asteroids) {
            if (!asteroid->isDead()) {
                asteroid->render(window);
            }
        }
    }
}

void ObjectManager::checkPowerUpCollisions() {
    if (!allPowerUpsDead() && player != nullptr) {
        for (const auto& powerUp : powerUps) {
            sf::FloatRect powerUpHitBox{powerUp->getHitBox()};
            sf::FloatRect playerHitBox{player->getHitBox()};

            if (utilities::checkCollision(powerUpHitBox, playerHitBox)) {
                if (powerUp->getName() == "Health") {
                    // TODO Make this a constant
                    player->increaseHealth(100);
                    logger.debug("Player collected Health Power Up", this);

                    // TODO Fix this sound not working
                    soundManager.startSound("healthPowerUpSound", assetManager.getSound("healthPowerUpSound"));
                } else if (powerUp->getName() == "Shield") {
                    player->setHasShield(true);
                    logger.debug("Player collected Shield Power Up", this);
                }
                powerUp->setIsUsed(true);
            }
        }
    }
}

void ObjectManager::checkAsteroidCollisions() {
    if (!allAsteroidsDead() && player != nullptr) {
        // Checking for collisions with player bullets
        auto playerBullets{player->getWeapon()->getBullets()};

        if (!playerBullets.empty()) {
            for (const auto& asteroid : asteroids) {
                sf::FloatRect asteroidHitBox{asteroid->getHitBox()};

                for (const auto& bullet : playerBullets) {
                    if (!bullet->isAlive()) {
                        continue;
                    }

                    sf::FloatRect bulletHitBox{bullet->getHitBox()};

                    if (utilities::checkCollision(bulletHitBox, asteroidHitBox)) {
                        bullet->setIsAlive(false);
                        // TODO Make this a constant
                        asteroid->takeDamage(10);
                        break;
                    }
                }
            }
        }

        // Checking for collisions with enemy bullets;
        auto enemies{enemyManager->getEnemies()};

        if (!enemies.empty()) {
            for (const auto& enemy : enemies) {
                auto bullets{enemy->getWeapon()->getBullets()};

                if (!bullets.empty()) {
                    for (const auto& bullet : bullets) {
                        if (!bullet->isAlive()) {
                            continue;
                        }

                        sf::FloatRect bulletHitBox{bullet->getHitBox()};

                        for (const auto& asteroid : asteroids) {
                            sf::FloatRect asteroidHitBox{asteroid->getHitBox()};
                            if (utilities::checkCollision(bulletHitBox, asteroidHitBox)) {
                                bullet->setIsAlive(false);
                                // TODO Make this a constant
                                asteroid->takeDamage(10);
                                break;
                            }
                        }
                    }
                }
            }
        }
    }
}

void ObjectManager::cleanUpPowerUps() {
    powerUps.erase(std::remove_if(std::begin(powerUps), std::end(powerUps), [](const auto& e) {
        return e->getIsUsed();
    }), std::end(powerUps));
}

void ObjectManager::cleanUpAsteroids() {

}

void ObjectManager::createPowerUp() {
    // TODO Make the creation of power up random
    sf::Vector2f pos{100, 1200};
    powerUps.emplace_back(std::make_unique<ShieldPowerUp>(pos, assetManager, soundManager));

    sf::Vector2f pos1{900, 1200};
    powerUps.emplace_back(std::make_unique<HealthPowerUp>(pos1, assetManager, soundManager));
}

bool ObjectManager::allPowerUpsDead() const {
    return powerUps.empty();
}

bool ObjectManager::allAsteroidsDead() const {
    return asteroids.empty();
}

void ObjectManager::initAsteroids() {
    // TODO Make the positions constants
    sf::Vector2f pos{300, 900};
    asteroids.emplace_back(std::make_unique<Asteroid>(pos, assetManager, soundManager));

    sf::Vector2f pos1{800, 900};
    asteroids.emplace_back(std::make_unique<Asteroid>(pos1, assetManager, soundManager));

    sf::Vector2f pos2{1300, 900};
    asteroids.emplace_back(std::make_unique<Asteroid>(pos2, assetManager, soundManager));
}
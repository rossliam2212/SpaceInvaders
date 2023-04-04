//
// Created by Liam Ross on 01/04/2023.
//

#include "ObjectManager.h"

ObjectManager::ObjectManager(Player* player, EnemyManager* enemyManager, AssetManager& assetManager, SoundManager& soundManager) noexcept
    : player{player},
      explosion{assetManager.getTexture("explosion")},
      explosionAnimation{explosion, 1, 3, Animation::FRAME_DURATION, false},
      explosionPlaying{false},
      explosionTimer{false},
      explosionCoolDown{EXPLOSION_COOL_DOWN_TIMER},
      enemyManager{enemyManager},
      assetManager{assetManager},
      soundManager{soundManager},
      logger{"logs"} {
    createPowerUp();
    initAsteroids();

    explosion.setScale(AssetManager::SPRITE_SCALE_UP_FACTOR + 5.f, AssetManager::SPRITE_SCALE_UP_FACTOR + 5.f);
}

void ObjectManager::update(const float& dt) {
    checkPowerUpCollisions();
    cleanUpPowerUps();
    checkAsteroidCollisions();
    cleanUpAsteroids();
    updateExplosionTimer(dt);

    if (explosionPlaying) {
        explosionAnimation.update(dt);
    }

    if (!allPowerUpsDead()) {
        for (const auto& powerUp : powerUps) {
            if (!powerUp->getIsUsed()) {
                powerUp->update(dt);
            }
        }
    }

    if (!allAsteroidsDead()) {
        for (const auto& asteroid : asteroids) {
            if (!asteroid->isDead()) {
                asteroid->update(dt);
            } else {
                explosionPlaying = true;
                createExplosion(asteroid->getPosition());
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

    if (explosionPlaying) {
        window->draw(explosion);
    }

    if (!allAsteroidsDead()) {
        for (const auto& asteroid : asteroids) {
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
                    logger.debug("Player collected Health Power Up", this, __LINE__);

                    // TODO Fix this sound not working
                    soundManager.startSound("healthPowerUpSound", assetManager.getSound("healthPowerUpSound"));
                } else if (powerUp->getName() == "Shield") {
                    player->setHasShield(true);
                    logger.debug("Player collected Shield Power Up", this, __LINE__);
                }
                powerUp->setIsUsed(true);
            }
        }
    }
}

void ObjectManager::checkAsteroidCollisions() {
    if (!allAsteroidsDead() && player != nullptr) {
        checkForCollisionsBetweenAsteroidAndPlayerBullets();
        checkForCollisionsBetweenAsteroidAndEnemyBullets();
    }
}

void ObjectManager::checkForCollisionsBetweenAsteroidAndPlayerBullets() {
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
                    asteroid->takeDamage(bullet->getDamageToAsteroid());
                    break;
                }
            }
        }
    }
}

void ObjectManager::checkForCollisionsBetweenAsteroidAndEnemyBullets() {
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
                            asteroid->takeDamage(bullet->getDamageToAsteroid());
                            break;
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
    asteroids.erase(std::remove_if(std::begin(asteroids), std::end(asteroids), [](const auto& e) {
        return e->isDead();
    }), std::end(asteroids));
}

void ObjectManager::createExplosion(const sf::Vector2f& position) {
    // TODO Fix explosion animation not working
    explosion.setPosition(position);
    explosionTimer = true;

    soundManager.startSound("explosionSound", assetManager.getSound("explosionSound"));
}

void ObjectManager::createPowerUp() {
    // TODO Make the creation of power up random
    sf::Vector2f pos{100, POWER_UP_SPAWN_POSITION_Y};
    powerUps.emplace_back(std::make_unique<ShieldPowerUp>(pos, assetManager, soundManager));

    sf::Vector2f pos1{900, POWER_UP_SPAWN_POSITION_Y};
    powerUps.emplace_back(std::make_unique<HealthPowerUp>(pos1, assetManager, soundManager));
}

bool ObjectManager::allPowerUpsDead() const {
    return powerUps.empty();
}

bool ObjectManager::allAsteroidsDead() const {
    return asteroids.empty();
}

void ObjectManager::updateExplosionTimer(const float& dt) {
    // Displays the explosion animation for a certain amount of time.
    if (explosionTimer) {
        explosionCoolDown -= dt;
        if (explosionCoolDown <= Animation::TIMER_ZERO) {
            explosionPlaying = false;
            explosionTimer = false;
            explosionCoolDown = EXPLOSION_COOL_DOWN_TIMER;

            soundManager.stopSound("explosionSound");
        }
    }
}

void ObjectManager::initAsteroids() {
    sf::Vector2f pos{ASTEROID_SPAWN_POSITION_X, ASTEROID_SPAWN_POSITION_Y};
    asteroids.emplace_back(std::make_unique<Asteroid>(pos, assetManager, soundManager));

    sf::Vector2f pos1{ASTEROID_SPAWN_POSITION_X + GAP_BETWEEN_ASTEROIDS, ASTEROID_SPAWN_POSITION_Y};
    asteroids.emplace_back(std::make_unique<Asteroid>(pos1, assetManager, soundManager));

    sf::Vector2f pos2{ASTEROID_SPAWN_POSITION_X + (GAP_BETWEEN_ASTEROIDS*2), ASTEROID_SPAWN_POSITION_Y};
    asteroids.emplace_back(std::make_unique<Asteroid>(pos2, assetManager, soundManager));
}
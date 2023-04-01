//
// Created by Liam Ross on 01/04/2023.
//

#include "ObjectManager.h"

ObjectManager::ObjectManager(Player* player, AssetManager& assetManager, SoundManager& soundManager) noexcept
    : player{player},
      assetManager{assetManager},
      soundManager{soundManager},
      logger{"logs"} {
    createPowerUp();
}

void ObjectManager::update(const float& dt) {
    checkCollisions();
    cleanUpPowerUps();

    if (!allPowerUpsDead()) {
        for (const auto& powerUp : powerUps) {
            if (!powerUp->getIsUsed()) {
                powerUp->update(dt);
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
}

void ObjectManager::checkCollisions() {
    if (!allPowerUpsDead() && player != nullptr) {
        for (const auto& powerUp : powerUps) {
            sf::FloatRect powerUpHitBox{powerUp->getHitBox()};
            sf::FloatRect playerHitBox{player->getHitBox()};

            if (utilities::checkCollision(powerUpHitBox, playerHitBox)) {
                if (powerUp->getName() == "Health") {
                    player->increaseHealth(100);
                    logger.debug("Player collected Health Power Up", this);

                    // TODO Fix this sound not working
                    soundManager.startSound("healthPowerUpSound", assetManager.getSound("healthPowerUpSound"));
                } else if (powerUp->getName() == "Shield") {
                    player->setHasShield(true);
                }
                powerUp->setIsUsed(true);
            }
        }
    }
}

void ObjectManager::cleanUpPowerUps() {
    powerUps.erase(std::remove_if(std::begin(powerUps), std::end(powerUps), [](const auto& e) {
        return e->getIsUsed();
    }), std::end(powerUps));
}

void ObjectManager::createPowerUp() {
    sf::Vector2f pos{100, 1200};
    powerUps.emplace_back(std::make_unique<ShieldPowerUp>(pos, assetManager, soundManager));

    sf::Vector2f pos1{900, 1200};
    powerUps.emplace_back(std::make_unique<HealthPowerUp>(pos1, assetManager, soundManager));
}

bool ObjectManager::allPowerUpsDead() const {
    return powerUps.empty();
}
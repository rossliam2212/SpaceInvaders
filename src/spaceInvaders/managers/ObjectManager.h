//
// Created by Liam Ross on 01/04/2023.
//

#ifndef SPACE_INVADERS_OBJECTMANAGER_H
#define SPACE_INVADERS_OBJECTMANAGER_H

#include <SFML/Graphics.hpp>
#include <memory>
#include <Logger.h>
#include <vector>

#include "../characters/Player.h"
#include "../objects/powerUps/HealthPowerUp.h"
#include "../objects/powerUps/ShieldPowerUp.h"

class ObjectManager {
private:
    // TODO Create vector to hold asteroids

    std::vector<std::unique_ptr<PowerUp>> powerUps;

    Player* player;
    AssetManager assetManager;
    SoundManager soundManager;

    logger::Logger logger;
public:
    ObjectManager(Player* player, AssetManager& assetManager, SoundManager& soundManager) noexcept;

    void update(const float& dt);
    void render(std::shared_ptr<sf::RenderWindow> window);

private:
    void checkCollisions();
    void cleanUpPowerUps();
    void createPowerUp();
    bool allPowerUpsDead() const;
};


#endif //SPACE_INVADERS_OBJECTMANAGER_H

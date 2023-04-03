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
#include "../objects/Asteroid.h"
#include "../managers/EnemyManager.h"

class ObjectManager {
private:
    static constexpr const float POWER_UP_SPAWN_POSITION_BOUNDARY_LEFT{50.f};
    static constexpr const float POWER_UP_SPAWN_POSITION_BOUNDARY_RIGHT{1450.f};
    static constexpr const float POWER_UP_SPAWN_POSITION_Y{1200.f};

    static constexpr const float ASTEROID_SPAWN_POSITION_X{250.f};
    static constexpr const float ASTEROID_SPAWN_POSITION_Y{900.f};
    static constexpr const float GAP_BETWEEN_ASTEROIDS{500.f};

    static constexpr const float TIMER_ZERO{0.f};
    static constexpr const float EXPLOSION_COOL_DOWN_TIMER{0.5f};

    std::vector<std::unique_ptr<Asteroid>> asteroids;
    std::vector<std::unique_ptr<PowerUp>> powerUps;

    Player* player;
    EnemyManager* enemyManager;

    sf::Sprite explosion;
    Animation explosionAnimation;
    bool explosionPlaying;
    bool explosionTimer;
    float explosionCoolDown;

    AssetManager assetManager;
    SoundManager soundManager;

    logger::Logger logger;

public:
    ObjectManager(Player* player, EnemyManager* enemyManager, AssetManager& assetManager, SoundManager& soundManager) noexcept;

    void update(const float& dt);
    void render(std::shared_ptr<sf::RenderWindow> window);

private:
    void checkPowerUpCollisions();
    void checkAsteroidCollisions();
    void checkForCollisionsBetweenAsteroidAndPlayerBullets();
    void checkForCollisionsBetweenAsteroidAndEnemyBullets();
    void createExplosion(const sf::Vector2f& position);
    void cleanUpPowerUps();
    void cleanUpAsteroids();
    void createPowerUp();
    bool allPowerUpsDead() const;
    bool allAsteroidsDead() const;

    void initAsteroids();
};


#endif //SPACE_INVADERS_OBJECTMANAGER_H

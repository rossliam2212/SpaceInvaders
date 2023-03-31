//
// Created by Liam Ross on 28/03/2023.
//

#ifndef SPACE_INVADERS_ENEMYMANAGER_H
#define SPACE_INVADERS_ENEMYMANAGER_H

#include <SFML/Graphics.hpp>
#include <memory>
#include <vector>
#include <array>
#include <Logger.h>
#include <chrono>

#include "../characters/Player.h"
#include "../characters/enemies/BlueEnemy.h"
#include "../characters/enemies/PurpleEnemy.h"
#include "../characters/enemies/YellowEnemy.h"
#include "../characters/enemies/GreenEnemy.h"

enum MoveDirection {
    moveLeft = 0,
    moveRight
};

class EnemyManager {
private:
    static constexpr const float ENEMY_START_POSITION_X{50.f};
    static constexpr const float ENEMY_START_POSITION_Y{150.f};
    static constexpr const float GAP_BETWEEN_ENEMIES_X{100.f};
    static constexpr const float GAP_BETWEEN_ENEMIES_Y{100.f};

    static constexpr const float ENEMY_MOVE_X_SPEED{50.f};
    static constexpr const float ENEMY_MOVE_Y_SPEED{20.f};

    static constexpr const int MAX_NUMBER_OF_BLUE_ENEMIES{10};
    static constexpr const int MAX_NUMBER_OF_GREEN_ENEMIES{10};
    static constexpr const int MAX_NUMBER_OF_YELLOW_ENEMIES{10};
    static constexpr const int MAX_NUMBER_OF_PURPLE_ENEMIES{10};

    static constexpr const float EXPLOSION_COOL_DOWN_TIMER{0.5f};

    Player* player;
    MoveDirection direction;

    sf::Sprite explosion;
    std::unique_ptr<Animation> explosionAnimation;
    bool explosionPlaying;
    bool explosionTimer;
    float explosionCoolDown;

    bool shooting{false};
    bool shootingTimer{false};
    float shootCoolDown{1.f};

    std::vector<std::unique_ptr<Enemy>> enemies;

    AssetManager assetManager;
    SoundManager soundManager;

    logger::Logger logger;

public:
    EnemyManager(Player* player, const AssetManager& assetManager, const SoundManager& soundManager) noexcept;

    void update(const float& dt);
    void render(std::shared_ptr<sf::RenderWindow> window);

private:
    void moveEnemiesX(const float& dt);
    void moveEnemiesY(const float& dt);
    void shoot();
    void createExplosion(const sf::Vector2f& position);

    bool allEnemiesDead();
    void checkCollisions();
    void cleanUpEnemies();
    MoveDirection getDirection(const float& dt);
    void initEnemies();
    void initAnimation();
};


#endif //SPACE_INVADERS_ENEMYMANAGER_H

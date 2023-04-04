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
#include "EnemyFactory.h"

class Player;

enum MoveDirection {
    moveLeft = 0,
    moveRight,
};

class EnemyManager {
private:
    static constexpr const float ENEMY_START_POSITION_X{50.f};
    static constexpr const float ENEMY_START_POSITION_Y{150.f};
    static constexpr const float GAP_BETWEEN_ENEMIES_X{100.f};
    static constexpr const float GAP_BETWEEN_ENEMIES_Y{100.f};

    static constexpr const float ENEMY_MOVE_X_SPEED{50.f};
    static constexpr const float ENEMY_MOVE_Y_SPEED{50.f};

    static constexpr const int MAX_NUMBER_OF_BLUE_ENEMIES{10};
    static constexpr const int MAX_NUMBER_OF_GREEN_ENEMIES{10};
    static constexpr const int MAX_NUMBER_OF_YELLOW_ENEMIES{10};
    static constexpr const int MAX_NUMBER_OF_PURPLE_ENEMIES{10};

    static constexpr const float MOVE_DOWN_TIMER{1.f};
    static constexpr const float EXPLOSION_COOL_DOWN_TIMER{0.5f};
    static constexpr const float SHOOT_COOL_DOWN_TIMER{3.f};

    Player* player;
    MoveDirection direction;

    sf::Sprite explosion;
    Animation explosionAnimation;

    bool explosionPlaying;
    bool explosionTimer;
    float explosionCoolDown;

    bool shooting;
    bool shootingTimer;
    float shootCoolDown;

    EnemyFactory enemyFactory;
    static const std::vector<std::tuple<std::string, int>> data;
    std::vector<std::unique_ptr<Enemy>> enemies;

    bool moveDown;
    bool moveDownTimer;
    float moveDownCoolDown;

    AssetManager assetManager;
    SoundManager soundManager;

    logger::Logger logger;

public:
    EnemyManager(Player* player, AssetManager& assetManager, SoundManager& soundManager) noexcept;

    void update(const float& dt);
    void render(std::shared_ptr<sf::RenderWindow> window);

    std::vector<Enemy*> getEnemies();

private:
    void moveEnemies(const float& dt);
    void shoot();
    void createExplosion(const sf::Vector2f& position);
    void updateExplosionTimer(const float& dt);
    void updateShootingTimer(const float& dt);
    void updateMoveDownTimer(const float& dt);
    bool allEnemiesDead();
    void checkCollisions();
    void cleanUpEnemies();
    void getDirection();
    void initEnemies();
};


#endif //SPACE_INVADERS_ENEMYMANAGER_H

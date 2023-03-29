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

class EnemyManager {
private:
    static constexpr const float START_POSITION_X{100.f};
    static constexpr const float START_POSITION_Y{100.f};
    static constexpr const float GAP_BETWEEN_ENEMIES_X{150.f};
    static constexpr const float GAP_BETWEEN_ENEMIES_Y{150.f};

    static constexpr const int MAX_NUMBER_OF_BLUE_ENEMIES{9};
    static constexpr const int MAX_NUMBER_OF_GREEN_ENEMIES{9};
    static constexpr const int MAX_NUMBER_OF_YELLOW_ENEMIES{9};
    static constexpr const int MAX_NUMBER_OF_PURPLE_ENEMIES{9};

    Player* player;
    sf::Sprite explosion;
    std::unique_ptr<Animation> explosionAnimation;
    bool explosionPlaying{false};
    bool explosionTimer{false};
    float explosionCoolDown{0.5f};

    std::vector<std::unique_ptr<Enemy>> enemies;
    int numberOfBlueEnemies;
    int numberOfGreenEnemies;
    int numberOfYellowEnemies;
    int numberOfPurpleEnemies;

    AssetManager assetManager;
    SoundManager soundManager;

    logger::Logger logger;

public:
    EnemyManager(Player* player, const AssetManager& assetManager, const SoundManager& soundManager) noexcept;

    void update(const float& dt);
    void render(std::shared_ptr<sf::RenderWindow> window);

private:
    void createExplosion(const sf::Vector2f& position);

    void checkCollisions();
    void cleanUpEnemies();
    void initEnemies();
    void initAnimation();
};


#endif //SPACE_INVADERS_ENEMYMANAGER_H

//
// Created by Liam Ross on 28/03/2023.
//

#ifndef SPACE_INVADERS_ENEMYMANAGER_H
#define SPACE_INVADERS_ENEMYMANAGER_H

#include <SFML/Graphics.hpp>
#include <memory>
#include <vector>
#include <Logger.h>

#include "../characters/Player.h"
#include "../characters/enemies/BlueEnemy.h"

class EnemyManager {
private:
    static constexpr const float START_POSITION_X{100.f};
    static constexpr const float START_POSITION_Y{100.f};

    static constexpr const int MAX_NUMBER_OF_BLUE_ENEMIES{12};
    static constexpr const int MAX_NUMBER_OF_GREEN_ENEMIES{5};
    static constexpr const int MAX_NUMBER_OF_YELLOW_ENEMIES{5};
    static constexpr const int MAX_NUMBER_OF_PURPLE_ENEMIES{5};

    Player* player;

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
    void checkCollisions();
    void cleanUpEnemies();
    void initEnemies();
};


#endif //SPACE_INVADERS_ENEMYMANAGER_H

//
// Created by Liam Ross on 28/03/2023.
//

#ifndef SPACE_INVADERS_ENEMYMANAGER_H
#define SPACE_INVADERS_ENEMYMANAGER_H

#include <SFML/Graphics.hpp>
#include <memory>
#include <vector>
#include <Logger.h>

#include "../characters/enemies/BlueEnemy.h"

class EnemyManager {
private:
    static constexpr const int MAX_NUMBER_OF_BLUE_ENEMIES{5};
    static constexpr const int MAX_NUMBER_OF_GREEN_ENEMIES{5};
    static constexpr const int MAX_NUMBER_OF_YELLOW_ENEMIES{5};
    static constexpr const int MAX_NUMBER_OF_PURPLE_ENEMIES{5};

    std::vector<std::unique_ptr<Enemy>> enemies;
    int numberOfBlueEnemies;
    int numberOfGreenEnemies;
    int numberOfYellowEnemies;
    int numberOfPurpleEnemies;

    AssetManager assetManager;
    SoundManager soundManager;

    logger::Logger logger;

public:
    EnemyManager(const AssetManager& assetManager, const SoundManager& soundManager) noexcept;

    void update(const float& dt);
    void render(std::shared_ptr<sf::RenderWindow> window);

private:
    void initEnemies();
};


#endif //SPACE_INVADERS_ENEMYMANAGER_H

//
// Created by Liam Ross on 31/03/2023.
//

#ifndef SPACE_INVADERS_ENEMYFACTORY_H
#define SPACE_INVADERS_ENEMYFACTORY_H

#include <memory>

#include "../characters/enemies/BlueEnemy.h"
#include "../characters/enemies/PurpleEnemy.h"
#include "../characters/enemies/YellowEnemy.h"
#include "../characters/enemies/GreenEnemy.h"

class EnemyFactory {
public:
    static std::unique_ptr<Enemy> createEnemy(const std::string& enemyType, const sf::Vector2f& position, AssetManager& assetManager, SoundManager& soundManager) ;
};


#endif //SPACE_INVADERS_ENEMYFACTORY_H

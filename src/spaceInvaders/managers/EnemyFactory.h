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
private:
    using CreateFunc = std::unique_ptr<Enemy> (*)(const sf::Vector2f&, AssetManager&, SoundManager&);

    std::unordered_map<std::string, CreateFunc> createFunctions;

public:
    EnemyFactory();
    std::unique_ptr<Enemy> createEnemy(const std::string& name, const sf::Vector2f& position, AssetManager& assetManager, SoundManager& soundManager);

private:
    void registerCreateFunc(const std::string& name, CreateFunc func);

    static std::unique_ptr<Enemy> createBlueEnemy(const sf::Vector2f& position, AssetManager& assetManager, SoundManager& soundManager);
    static std::unique_ptr<Enemy> createGreenEnemy(const sf::Vector2f& position, AssetManager& assetManager, SoundManager& soundManager);
    static std::unique_ptr<Enemy> createYellowEnemy(const sf::Vector2f& position, AssetManager& assetManager, SoundManager& soundManager);
    static std::unique_ptr<Enemy> createPurpleEnemy(const sf::Vector2f& position, AssetManager& assetManager, SoundManager& soundManager);
};


#endif //SPACE_INVADERS_ENEMYFACTORY_H

//
// Created by Liam Ross on 31/03/2023.
//

#include "EnemyFactory.h"

EnemyFactory::EnemyFactory() {
    registerCreateFunc("Blue", &createBlueEnemy);
    registerCreateFunc("Green", &createGreenEnemy);
    registerCreateFunc("Yellow", &createYellowEnemy);
    registerCreateFunc("Purple", &createPurpleEnemy);
}

std::unique_ptr<Enemy> EnemyFactory::createEnemy(const std::string& name, const sf::Vector2f& position, AssetManager& assetManager, SoundManager& soundManager) {
    auto it = createFunctions.find(name);

    if (it != std::end(createFunctions)) {
        return it->second(position, assetManager, soundManager);
    } else {
        throw std::runtime_error("Unknown enemy type: " + name);
    }
}

void EnemyFactory::registerCreateFunc(const std::string& name, CreateFunc func) {
    createFunctions[name] = func;
}

std::unique_ptr<Enemy> EnemyFactory::createBlueEnemy(const sf::Vector2f& position, AssetManager& assetManager, SoundManager& soundManager) {
    return std::make_unique<BlueEnemy>(position, assetManager, soundManager);
}

std::unique_ptr<Enemy> EnemyFactory::createGreenEnemy(const sf::Vector2f& position, AssetManager& assetManager, SoundManager& soundManager) {
    return std::make_unique<GreenEnemy>(position, assetManager, soundManager);
}

std::unique_ptr<Enemy> EnemyFactory::createYellowEnemy(const sf::Vector2f& position, AssetManager& assetManager, SoundManager& soundManager) {
    return std::make_unique<YellowEnemy>(position, assetManager, soundManager);
}

std::unique_ptr<Enemy> EnemyFactory::createPurpleEnemy(const sf::Vector2f& position, AssetManager& assetManager, SoundManager& soundManager) {
    return std::make_unique<PurpleEnemy>(position, assetManager, soundManager);
}

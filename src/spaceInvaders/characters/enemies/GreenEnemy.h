//
// Created by Liam Ross on 28/03/2023.
//

#ifndef SPACE_INVADERS_GREENENEMY_H
#define SPACE_INVADERS_GREENENEMY_H

#include "../Enemy.h"

class GreenEnemy : public Enemy {
private:
    static constexpr const char* GREEN_ENEMY_NAME{"Green Enemy"};

public:
    GreenEnemy(const sf::Vector2f& position, const AssetManager& assetManager, const SoundManager& soundManager) noexcept;
    ~GreenEnemy() override = default;
};


#endif //SPACE_INVADERS_GREENENEMY_H

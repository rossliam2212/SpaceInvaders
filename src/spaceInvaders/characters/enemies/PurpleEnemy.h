//
// Created by Liam Ross on 28/03/2023.
//

#ifndef SPACE_INVADERS_PURPLEENEMY_H
#define SPACE_INVADERS_PURPLEENEMY_H

#include "../Enemy.h"

class PurpleEnemy : public Enemy {
private:
    static constexpr const char* PURPLE_ENEMY_NAME{"Purple Enemy"};

public:
    PurpleEnemy(const sf::Vector2f& position, const AssetManager& assetManager, const SoundManager& soundManager) noexcept;
    ~PurpleEnemy() override = default;
};


#endif //SPACE_INVADERS_PURPLEENEMY_H

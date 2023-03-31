//
// Created by Liam Ross on 28/03/2023.
//

#ifndef SPACE_INVADERS_PURPLEENEMY_H
#define SPACE_INVADERS_PURPLEENEMY_H

#include "../Enemy.h"

class PurpleEnemy : public Enemy {
private:
    static constexpr const char* PURPLE_ENEMY_NAME{"Purple Enemy"};
    static constexpr const int PURPLE_ENEMY_SCORE_WORTH{40};

public:
    PurpleEnemy(const sf::Vector2f& position, AssetManager& assetManager, SoundManager& soundManager) noexcept;
    ~PurpleEnemy() override = default;
};


#endif //SPACE_INVADERS_PURPLEENEMY_H

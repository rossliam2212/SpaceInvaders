//
// Created by Liam Ross on 28/03/2023.
//

#ifndef SPACE_INVADERS_BLUEENEMY_H
#define SPACE_INVADERS_BLUEENEMY_H

#include "../Enemy.h"

class BlueEnemy : public Enemy {
private:
    static constexpr const char* BLUE_ENEMY_NAME{"Blue Enemy"};
    static constexpr const int BLUE_ENEMY_SCORE_WORTH{10};

public:
    BlueEnemy(const sf::Vector2f& position, const AssetManager& assetManager, const SoundManager& soundManager) noexcept;
    ~BlueEnemy() override = default;
};


#endif //SPACE_INVADERS_BLUEENEMY_H

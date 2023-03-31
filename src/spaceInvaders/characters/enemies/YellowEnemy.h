//
// Created by Liam Ross on 28/03/2023.
//

#ifndef SPACE_INVADERS_YELLOWENEMY_H
#define SPACE_INVADERS_YELLOWENEMY_H

#include "../Enemy.h"

class YellowEnemy : public Enemy {
private:
    static constexpr const char* YELLOW_ENEMY_NAME{"Yellow Enemy"};
    static constexpr const int YELLOW_ENEMY_SCORE_WORTH{20};

public:
    YellowEnemy(const sf::Vector2f& position, AssetManager& assetManager, SoundManager& soundManager) noexcept;
    ~YellowEnemy() override = default;
};


#endif //SPACE_INVADERS_YELLOWENEMY_H

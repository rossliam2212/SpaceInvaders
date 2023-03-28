//
// Created by Liam Ross on 28/03/2023.
//

#ifndef SPACE_INVADERS_YELLOWENEMY_H
#define SPACE_INVADERS_YELLOWENEMY_H

#include "../Enemy.h"

class YellowEnemy : public Enemy {
private:
    static constexpr const char* YELLOW_ENEMY_NAME{"Yellow Enemy"};

public:
    YellowEnemy(const sf::Vector2f& position, const AssetManager& assetManager, const SoundManager& soundManager) noexcept;
    ~YellowEnemy() override = default;
};


#endif //SPACE_INVADERS_YELLOWENEMY_H

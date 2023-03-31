//
// Created by Liam Ross on 31/03/2023.
//

#ifndef SPACE_INVADERS_ENEMYWEAPON_H
#define SPACE_INVADERS_ENEMYWEAPON_H

#include "Weapon.h"
#include "../bullets/EnemyBullet.h"

class EnemyWeapon : public Weapon {
private:
    static constexpr const float ENEMY_WEAPON_SHOOT_COOL_DOWN{1.f};

public:
    EnemyWeapon(AssetManager& assetManager, SoundManager& soundManager) noexcept;
    ~EnemyWeapon() override = default;

    void update(const float& dt) override;
    void render(std::shared_ptr<sf::RenderWindow> window) override;

    void shoot(const sf::Vector2f& shootPosition) override;
};


#endif //SPACE_INVADERS_ENEMYWEAPON_H

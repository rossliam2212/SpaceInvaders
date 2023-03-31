//
// Created by Liam Ross on 28/03/2023.
//

#ifndef SPACE_INVADERS_PLAYERWEAPON_H
#define SPACE_INVADERS_PLAYERWEAPON_H

#include "Weapon.h"
#include "../bullets/PlayerBullet.h"

class PlayerWeapon : public Weapon {
private:
    static constexpr const float PLAYER_WEAPON_SHOOT_COOL_DOWN{1.f};

public:
    PlayerWeapon(AssetManager& assetManager, SoundManager& soundManager) noexcept;
    ~PlayerWeapon() override = default;

    void update(const float& dt) override;
    void render(std::shared_ptr<sf::RenderWindow> window) override;

    void shoot(const sf::Vector2f& shootPosition) override;
};


#endif //SPACE_INVADERS_PLAYERWEAPON_H

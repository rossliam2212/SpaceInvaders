//
// Created by Liam Ross on 28/03/2023.
//

#ifndef SPACE_INVADERS_PLAYERWEAPON_H
#define SPACE_INVADERS_PLAYERWEAPON_H

#include "Weapon.h"
#include "PlayerBullet.h"

class PlayerWeapon : public Weapon {
private:
    static constexpr const float PLAYER_WEAPON_BULLET_SPEED{10.f};
    static constexpr const float PLAYER_WEAPON_FIRE_RATE{0.5f};

public:
    PlayerWeapon(float fireRate, const sf::Vector2f& shootPosition, const AssetManager& assetManager, const SoundManager& soundManager) noexcept;
    ~PlayerWeapon() override = default;

    void update(const float& dt) override;
    void render(std::shared_ptr<sf::RenderWindow> window) override;

    void shoot() override;
};


#endif //SPACE_INVADERS_PLAYERWEAPON_H

//
// Created by Liam Ross on 27/03/2023.
//

#ifndef SPACE_INVADERS_WEAPON_H
#define SPACE_INVADERS_WEAPON_H

#include <vector>

#include "Bullet.h"

class Weapon {
protected:
    std::vector<std::unique_ptr<Bullet>> bullets;

    sf::Vector2f shootPosition;

    float bulletSpeed;
    float fireRate;
    float timeSinceLastShot;

    AssetManager assetManager;
    SoundManager soundManager;

public:
    Weapon(float bulletSpeed, float fireRate, const sf::Vector2f& shootPosition,
           const AssetManager& assetManager, const SoundManager& soundManager) noexcept;
    virtual ~Weapon() = default;

    virtual void update(const float& dt) = 0;
    virtual void render(std::shared_ptr<sf::RenderWindow> window) = 0;

    virtual void shoot() = 0;

    float getBulletSpeed() const;
    float getFireRate() const;
    sf::Vector2f getShootPosition() const;
};


#endif //SPACE_INVADERS_WEAPON_H

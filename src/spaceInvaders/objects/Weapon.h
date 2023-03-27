//
// Created by Liam Ross on 27/03/2023.
//

#ifndef SPACE_INVADERS_WEAPON_H
#define SPACE_INVADERS_WEAPON_H

#include <vector>

#include "../managers/AssetManager.h"
#include "Bullet.h"
#include "../managers/SoundManager.h"

class Weapon {
private:
    sf::Sprite bulletSprite;
    std::vector<std::unique_ptr<Bullet>> bullets;

    sf::Vector2f shootPosition;

    int damage;
    float bulletSpeed;
    float fireRate;
    float timeSinceLastShot;

    AssetManager assetManager;
    SoundManager soundManager;

public:
    Weapon(int damage, float bulletSpeed, float fireRate, const sf::Vector2f& shootPosition,
           const AssetManager& assetManager, const SoundManager& soundManager) noexcept;
    virtual ~Weapon() = default;

    void update(const float& dt);
    void render(std::shared_ptr<sf::RenderWindow> window);

    void shoot();

    int getDamage() const;
    float getBulletSpeed() const;
    float getFireRate() const;
    sf::Vector2f getShootPosition() const;

protected:
    void initBulletSprite(const std::string& textureName);
};


#endif //SPACE_INVADERS_WEAPON_H

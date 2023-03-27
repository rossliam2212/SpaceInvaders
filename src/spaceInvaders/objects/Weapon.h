//
// Created by Liam Ross on 27/03/2023.
//

#ifndef SPACE_INVADERS_WEAPON_H
#define SPACE_INVADERS_WEAPON_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>

class Weapon {
private:
    // Bullet sprite/texture
    // vector of bullets

    sf::Vector2f shootPosition;

    int damage;
    float bulletSpeed;
    float fireRate;
    float timeSinceLastShot;


public:
    Weapon(int damage, float bulletSpeed, float fireRate, const sf::Vector2f& shootPosition) noexcept;

    void update(const float& dt);
    void render(std::shared_ptr<sf::RenderWindow> window);

    void shoot();

    int getDamage() const;
    float getBulletSpeed() const;
    float getFireRate() const;
    sf::Vector2f getShootPosition() const;
};


#endif //SPACE_INVADERS_WEAPON_H

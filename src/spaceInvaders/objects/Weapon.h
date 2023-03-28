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

    float shootCoolDown;
    bool isShooting;
    bool shootCoolDownTimer;

    AssetManager assetManager;
    SoundManager soundManager;

public:
    Weapon(float shootCoolDown, const AssetManager& assetManager, const SoundManager& soundManager) noexcept;
    virtual ~Weapon() = default;

    virtual void update(const float& dt) = 0;
    virtual void render(std::shared_ptr<sf::RenderWindow> window) = 0;

    virtual void shoot(const sf::Vector2f& shootPosition) = 0;

    std::vector<std::unique_ptr<Bullet>>& getBullets();
    float getShootCoolDown() const;

    bool getIsShooting() const;
    void setIsShooting(bool shooting);

    bool getShootCoolDownTimer() const;
    void setShootCoolDownTimer(bool timer);
};


#endif //SPACE_INVADERS_WEAPON_H

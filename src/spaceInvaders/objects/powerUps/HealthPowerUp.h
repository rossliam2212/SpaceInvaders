//
// Created by Liam Ross on 01/04/2023.
//

#ifndef SPACE_INVADERS_HEALTHPOWERUP_H
#define SPACE_INVADERS_HEALTHPOWERUP_H

#include "PowerUp.h"

class HealthPowerUp : public PowerUp {
private:
    static constexpr const char* POWER_UP_NAME{"Health"};

public:
    HealthPowerUp(const sf::Vector2f& position, AssetManager& assetManager, SoundManager& soundManager) noexcept;
    ~HealthPowerUp() override = default;

    void update(const float& dt) override;
    void render(std::shared_ptr<sf::RenderWindow> window) override;
};


#endif //SPACE_INVADERS_HEALTHPOWERUP_H

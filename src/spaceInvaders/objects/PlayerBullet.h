//
// Created by Liam Ross on 28/03/2023.
//

#ifndef SPACE_INVADERS_PLAYERBULLET_H
#define SPACE_INVADERS_PLAYERBULLET_H

#include "Bullet.h"

class PlayerBullet : public Bullet {
private:
    static constexpr const int PLAYER_BULLET_DAMAGE{120};
    static constexpr const float PLAYER_BULLET_SPEED_MULTIPLIER{25.f};
    static constexpr const float PLAYER_BULLET_SPEED{30.f};

public:
    PlayerBullet(const sf::Vector2f& spawnPosition, const AssetManager& assetManager,const SoundManager& soundManager) noexcept;
    ~PlayerBullet() override = default;

    void update(const float& dt) override;
    void render(std::shared_ptr<sf::RenderWindow> window) override;
};


#endif //SPACE_INVADERS_PLAYERBULLET_H

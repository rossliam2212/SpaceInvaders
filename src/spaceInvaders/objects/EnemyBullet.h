//
// Created by Liam Ross on 31/03/2023.
//

#ifndef SPACE_INVADERS_ENEMYBULLET_H
#define SPACE_INVADERS_ENEMYBULLET_H

#include "Bullet.h"

class EnemyBullet : public Bullet {
private:
    static constexpr const int ENEMY_BULLET_DAMAGE{20};
    static constexpr const float ENEMY_BULLET_SPEED_MULTIPLIER{25.f};
    static constexpr const float ENEMY_BULLET_SPEED{30.f};

public:
    EnemyBullet(const sf::Vector2f& spawnPosition, const AssetManager& assetManager,const SoundManager& soundManager) noexcept;
    ~EnemyBullet() override = default;

    void update(const float& dt) override;
    void render(std::shared_ptr<sf::RenderWindow> window) override;
};


#endif //SPACE_INVADERS_ENEMYBULLET_H

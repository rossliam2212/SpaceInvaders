//
// Created by Liam Ross on 28/03/2023.
//

#ifndef SPACE_INVADERS_ENEMY_H
#define SPACE_INVADERS_ENEMY_H

#include "Character.h"
#include "../objects/weapons/EnemyWeapon.h"

class Enemy : public Character {
protected:
    static constexpr const float DEFAULT_ENEMY_MOVE_SPEED{1.f};

    EnemyWeapon weapon;
    int scoreWorth;
    bool isShooting;

    bool drawExplosion{false};
    sf::Sprite explosion;
    std::unique_ptr<Animation> explosionAnimation;

public:
    Enemy(const std::string& name, const sf::Vector2f& position, int scoreWorth, AssetManager& assetManager, SoundManager& soundManager) noexcept;
    ~Enemy() override = default;

    void update(const float& dt) override;
    void render(std::shared_ptr<sf::RenderWindow> window) override;

    void moveX(const float& dt, float directionX);
    void moveY(const float& dt, float directionY);

    void shoot(const sf::Vector2f& shootPosition);

    int getScoreWorth() const;

protected:
    void initSprite(const sf::Texture& texture);
};


#endif //SPACE_INVADERS_ENEMY_H

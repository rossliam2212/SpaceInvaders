//
// Created by Liam Ross on 27/03/2023.
//

#ifndef SPACE_INVADERS_BULLET_H
#define SPACE_INVADERS_BULLET_H

#include <SFML/Graphics.hpp>
#include <memory>
#include <string>

#include "../managers/AssetManager.h"
#include "../managers/SoundManager.h"

class Bullet {
protected:
    sf::Sprite sprite;
    sf::Vector2f spawnPosition;

    int damage;
    float lifeTime;
    float timeAlive;

    AssetManager assetManager;
    SoundManager soundManager;

public:
    Bullet(int damage, float lifeTime, const sf::Vector2f& spawnPosition,
           const AssetManager& assetManager, const SoundManager& soundManager) noexcept;
    virtual ~Bullet() = default;

    virtual void update(const float& dt) = 0;
    virtual void render(std::shared_ptr<sf::RenderWindow> window) = 0;

    int getDamage() const;
    float getLifeTime() const;
    float getTimeAlive() const;
    bool isAlive() const;

protected:
    void initSprite(const std::string& textureName);
};


#endif //SPACE_INVADERS_BULLET_H

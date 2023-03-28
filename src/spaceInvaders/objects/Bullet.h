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
    bool alive;

    AssetManager assetManager;
    SoundManager soundManager;

public:
    Bullet(int damage, const sf::Vector2f& spawnPosition,
           const AssetManager& assetManager, const SoundManager& soundManager) noexcept;
    virtual ~Bullet() = default;

    virtual void update(const float& dt) = 0;
    virtual void render(std::shared_ptr<sf::RenderWindow> window) = 0;

    int getDamage() const;
    bool isAlive() const;
    sf::Vector2f getPosition() const;
    sf::FloatRect getHitBox() const;

protected:
    void initSprite(const std::string& textureName);
    void checkForBulletOffScreen();
};


#endif //SPACE_INVADERS_BULLET_H

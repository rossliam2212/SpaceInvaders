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
#include "../utilities/Utils.h"

class Bullet {
private:
    static constexpr const int WINDOW_WIDTH{1500};
    static constexpr const int WINDOW_HEIGHT{1500};

protected:
    sf::Sprite sprite;
    sf::Vector2f spawnPosition;

    int damage;
    bool alive;

    AssetManager assetManager;
    SoundManager soundManager;

public:
    Bullet(int damage, const sf::Vector2f& spawnPosition, AssetManager& assetManager, SoundManager& soundManager) noexcept;
    virtual ~Bullet() = default;

    virtual void update(const float& dt) = 0;
    virtual void render(std::shared_ptr<sf::RenderWindow> window) = 0;

    int getDamage() const;
    bool isAlive() const;
    void setIsAlive(bool isAlive);
    sf::Vector2f getPosition() const;
    sf::FloatRect getHitBox() const;

protected:
    void initSprite(const sf::Texture& texture);
    void checkForBulletOffScreen();
};


#endif //SPACE_INVADERS_BULLET_H

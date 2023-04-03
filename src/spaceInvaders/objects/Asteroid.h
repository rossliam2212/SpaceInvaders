//
// Created by Liam Ross on 02/04/2023.
//

#ifndef SPACE_INVADERS_ASTEROID_H
#define SPACE_INVADERS_ASTEROID_H

#include "Animation.h"
#include "../characters/Entity.h"
#include "../managers/AssetManager.h"
#include "../managers/SoundManager.h"

class Asteroid : public Entity {
private:
    static constexpr const char* ASTEROID_NAME{"Asteroid"};
    static constexpr const int ASTEROID_MAX_HEALTH{100};

    sf::Sprite sprite;
    sf::Text healthText;
    int health;
    bool dead;

    AssetManager assetManager;
    SoundManager soundManager;

public:
    Asteroid(const sf::Vector2f& position, AssetManager& assetManager, SoundManager& soundManager) noexcept;
    ~Asteroid() override = default;

    void update(const float& dt);
    void render(std::shared_ptr<sf::RenderWindow> window);

    void takeDamage(int damage);
    int getHealth() const;
    static int getMaxHealth();

    sf::FloatRect getHitBox() const;
    bool isDead() const;

private:
    void initText();
    void initSprite();
};


#endif //SPACE_INVADERS_ASTEROID_H

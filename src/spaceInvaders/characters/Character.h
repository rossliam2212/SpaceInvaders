//
// Created by Liam Ross on 24/03/2023.
//

#ifndef SPACE_INVADERS_CHARACTER_H
#define SPACE_INVADERS_CHARACTER_H

#include <unordered_map>
#include <vector>
#include <memory>

#include "Entity.h"
#include "../objects/Animation.h"
#include "../managers/SoundManager.h"
#include "../managers/AssetManager.h"
#include "../input/Input.h"

class Character : public Entity {
protected:
    static constexpr const int SPRITE_SCALE_FACTOR{10};
    static constexpr const int MAX_HEALTH{100};
    static constexpr const int MIN_HEALTH{100};
    static constexpr const float SPEED_MULTIPLIER{50.f};

    sf::Sprite sprite;

    int health;
    float speed;
    bool dead;

    AssetManager assetManager;
    SoundManager soundManager;

public:
    Character(const std::string& name, const sf::Vector2f& position, float speed, const AssetManager& assetManager, const SoundManager& soundManager) noexcept;
    ~Character() override = default;

    virtual void update(const float& dt) = 0;
    virtual void render(std::shared_ptr<sf::RenderWindow> window) = 0;

    void move(const float& dt, float directionX);

    void increaseHealth(int healthIncrease);
    void takeDamage(int damage);
    void kill();

    int getHealth() const;
    float getSpeed() const;
    bool isDead() const;

protected:
    void initSprite(const std::string& textureName);
};


#endif //SPACE_INVADERS_CHARACTER_H

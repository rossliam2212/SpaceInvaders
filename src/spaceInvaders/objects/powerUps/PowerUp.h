//
// Created by Liam Ross on 01/04/2023.
//

#ifndef SPACE_INVADERS_POWERUP_H
#define SPACE_INVADERS_POWERUP_H

#include <SFML/Graphics.hpp>
#include <memory>

#include "../../characters/Entity.h"
#include "../../managers/AssetManager.h"
#include "../../managers/SoundManager.h"

class PowerUp : public Entity {
protected:
    sf::Sprite sprite;

    AssetManager assetManager;
    SoundManager soundManager;

    bool isUsed;

public:
    PowerUp(const std::string& name, const sf::Vector2f& position, AssetManager& assetManager, SoundManager& soundManager) noexcept;
    ~PowerUp() override = default;

    virtual void update(const float& dt) = 0;
    virtual void render(std::shared_ptr<sf::RenderWindow> window) = 0;

    void setIsUsed(bool used);
    bool getIsUsed() const;

    sf::FloatRect getHitBox() const;

protected:
    void initSprite(const sf::Texture& texture);
};


#endif //SPACE_INVADERS_POWERUP_H

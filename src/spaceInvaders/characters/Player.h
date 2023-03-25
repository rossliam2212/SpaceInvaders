//
// Created by Liam Ross on 25/03/2023.
//

#ifndef SPACE_INVADERS_PLAYER_H
#define SPACE_INVADERS_PLAYER_H

#include "Character.h"

class Player : public Character {
private:
    static constexpr const char* PLAYER_NAME{"Player"};
    static constexpr const float PLAYER_SPEED{5.f};

    sf::Vector2f moveDirection;

public:
    Player(const sf::Vector2f& position, const AssetManager& assetManager, const SoundManager& soundManager) noexcept;
    Player(const std::string& name, const sf::Vector2f& position, float speed, const AssetManager& assetManager, const SoundManager& soundManager) noexcept;
    ~Player() override = default;

    void update(const float& dt) override;
    void render(std::shared_ptr<sf::RenderWindow> window) override;

private:
    void getInput(const float& dt);
};


#endif //SPACE_INVADERS_PLAYER_H

//
// Created by Liam Ross on 25/03/2023.
//

#ifndef SPACE_INVADERS_PLAYER_H
#define SPACE_INVADERS_PLAYER_H

#include "Character.h"

enum Move {
    still = 0,
    left,
    right
};

class Player : public Character {
private:
    static constexpr const char* PLAYER_NAME{"Player"};
    static constexpr const float START_POSITION_X{750.f};
    static constexpr const float START_POSITION_Y{1200.f};
    static constexpr const float PLAYER_SPEED{5.f};

    sf::Vector2f moveDirection;
    Move moveState{still};

    std::unordered_map<Move, std::unique_ptr<Animation>> animations;

public:
    Player(const AssetManager& assetManager, const SoundManager& soundManager) noexcept;
    Player(const sf::Vector2f& position, const AssetManager& assetManager, const SoundManager& soundManager) noexcept;
    Player(const std::string& name, const sf::Vector2f& position, float speed, const AssetManager& assetManager, const SoundManager& soundManager) noexcept;
    ~Player() override = default;

    void update(const float& dt) override;
    void render(std::shared_ptr<sf::RenderWindow> window) override;

private:
    void getInput(const float& dt);
    void checkForSpriteChange();

    void initAnimations();
};


#endif //SPACE_INVADERS_PLAYER_H

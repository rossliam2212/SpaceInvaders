//
// Created by Liam Ross on 25/03/2023.
//

#ifndef SPACE_INVADERS_PLAYER_H
#define SPACE_INVADERS_PLAYER_H

#include "Character.h"
#include "../objects/weapons/PlayerWeapon.h"
#include "../utilities/Utils.h"
#include "../managers/EnemyManager.h"


class EnemyManager;

enum MoveState {
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

    static constexpr const float SHOOT_POSITION_OFFSET_LEFT{30.f};
    static constexpr const float SHOOT_POSITION_OFFSET_RIGHT{40.f};

    static constexpr const int MAX_PLAYER_SHIELD_HEALTH{100.f};

    sf::Vector2f moveDirection;
    MoveState moveState{still};

    // TODO Add animation for player death
    std::unordered_map<MoveState, std::unique_ptr<Animation>> animations;

    PlayerWeapon weapon;
    sf::Vector2f shootPosition;
    bool isShootPressed;

    int shieldHealth;
    bool hasShield;

    EnemyManager* enemyManager; // Needs access to the enemies for collision checking

    // TODO Add stats for number of each type of enemy killed
    int score;
    std::unordered_map<std::string, int> killStats;

public:
    Player(AssetManager& assetManager, SoundManager& soundManager, EnemyManager* enemyManager) noexcept;
    Player(const sf::Vector2f& position, AssetManager& assetManager, SoundManager& soundManager, EnemyManager* enemyManager) noexcept;
    Player(const std::string& name, const sf::Vector2f& position, float speed, AssetManager& assetManager, SoundManager& soundManager, EnemyManager* enemyManager) noexcept;
    ~Player() override = default;

    void update(const float& dt) override;
    void render(std::shared_ptr<sf::RenderWindow> window) override;

    PlayerWeapon* getWeapon();

    int getShieldHealth() const;
    bool getHasShield() const;

    void updateKillStats(const std::string& enemyKilled);
    void increaseScore(int scoreAmount);
    int getScore() const;

private:
    void shoot();
    void updateWeapons(const float& dt);

    void getInput(const float& dt);

    void checkCollisions();
    void updateAnimations(const float& dt);
    void checkForSpriteChange();

    void initAnimations();
    void initStats();
};


#endif //SPACE_INVADERS_PLAYER_H

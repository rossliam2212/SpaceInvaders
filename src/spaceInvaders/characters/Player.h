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

struct Stats {
    int score;
    std::unordered_map<std::string, int> killStats;

    Stats() : score{} {
        killStats["Blue Enemy"] = 0;
        killStats["Yellow Enemy"] = 0;
        killStats["Green Enemy"] = 0;
        killStats["Purple Enemy"] = 0;
    }
};

class Player : public Character {
private:
    static constexpr const char* PLAYER_NAME{"Player"};
    static constexpr const float START_POSITION_X{750.f};
    static constexpr const float START_POSITION_Y{1200.f};
    static constexpr const float PLAYER_SPEED{5.f};

    static constexpr const float SHOOT_POSITION_OFFSET_LEFT{30.f};
    static constexpr const float SHOOT_POSITION_OFFSET_RIGHT{40.f};

    static constexpr const float EXPLOSION_COOL_DOWN_TIMER{0.5f};
    static constexpr const float SHIELD_COOL_DOWN_TIMER{0.5f};
    static constexpr const float DEATH_COOL_DOWN_TIMER{0.5f};

    static constexpr const int MAX_PLAYER_SHIELD_HEALTH{100};
    static constexpr const float SHIELD_OFFSET_X{40.f};
    static constexpr const float SHIELD_OFFSET_Y{25.f};

    sf::Vector2f moveDirection;
    MoveState moveState{still};

    std::unordered_map<MoveState, std::unique_ptr<Animation>> animations;

    sf::Sprite explosion;
    Animation explosionAnimation;
    bool explosionPlaying;
    bool explosionTimer;
    float explosionCoolDown;

    bool deathTimer;
    float deathCoolDown;

    PlayerWeapon weapon;
    sf::Vector2f shootPosition;
    bool isShootPressed;


    sf::Sprite shield;
    Animation shieldAnimation;
    bool shieldPlaying;
    bool shieldTimer;
    float shieldCoolDown;
    int shieldHealth;
    bool hasShield;

    EnemyManager* enemyManager; // Needs access to the enemies for collision checking

    Stats playerStats;

public:
    Player(AssetManager& assetManager, SoundManager& soundManager, EnemyManager* enemyManager) noexcept;
    ~Player() override = default;

    void update(const float& dt) override;
    void render(std::shared_ptr<sf::RenderWindow> window) override;

    void takeShieldDamage(int damage);
    void kill() override;

    PlayerWeapon* getWeapon();

    int getShieldHealth() const;
    bool getHasShield() const;
    void setHasShield(bool shieldActive);
    static int getShieldMaxHealth() ;

    void updateKillStats(const std::string& enemyKilled);
    void increaseScore(int scoreAmount);
    Stats getPlayerStats() const;

private:
    void shoot();
    void updateWeapons(const float& dt);
    void updateDeathTimer(const float& dt);
    void updateExplosionTimer(const float& dt);
    void updateShieldTimer(const float& dt);

    void getInput(const float& dt);

    void createExplosion();
    void checkCollisions();
    void updateAnimations(const float& dt);
    void checkForSpriteChange();

    void initAnimations();
};


#endif //SPACE_INVADERS_PLAYER_H

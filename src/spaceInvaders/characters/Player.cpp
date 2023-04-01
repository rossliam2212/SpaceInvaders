//
// Created by Liam Ross on 25/03/2023.
//

#include "Player.h"

Player::Player(AssetManager& assetManager, SoundManager& soundManager, EnemyManager* enemyManager) noexcept
    : Character{PLAYER_NAME, sf::Vector2f{START_POSITION_X, START_POSITION_Y}, PLAYER_SPEED, assetManager, soundManager},
      moveState{still},
      explosion{assetManager.getTexture("explosion")},
      explosionAnimation{explosion, 1, 3, Animation::FRAME_DURATION, false},
      explosionPlaying{false},
      explosionTimer{false},
      explosionCoolDown{EXPLOSION_COOL_DOWN_TIMER},
      deathTimer{false},
      deathCoolDown{DEATH_COOL_DOWN_TIMER},
      weapon{assetManager, soundManager},
      playerStats{},
      isShootPressed{false},
      shield{assetManager.getTexture("shieldAnimation")},
      shieldAnimation{shield, 1, 4, Animation::FRAME_DURATION, false},
      shieldPlaying{false},
      shieldTimer{false},
      shieldCoolDown{SHIELD_COOL_DOWN_TIMER},
      shieldHealth{MAX_PLAYER_SHIELD_HEALTH},
      hasShield{false},
      enemyManager{enemyManager}{
    logger.info("Player initialized.", this);
    initAnimations();
}

void Player::update(const float& dt) {
    // Only update the explosion animation when the player has been killed
    if (explosionPlaying) {
//        shield.setPosition(sprite.getPosition());
        explosionAnimation.update(dt);
    }

    updateDeathTimer(dt);
    updateExplosionTimer(dt);
    updateShieldTimer(dt);

    if (shieldPlaying) {
        shieldAnimation.update(dt);
    }

    // Don't update the player after death
    if (!explosionPlaying && !deathTimer) {
        checkCollisions();
        getInput(dt);
        move(dt, moveDirection.x);

        if (hasShield) {
            move(dt, shield, moveDirection.x);
        }

        updateAnimations(dt);
        updateWeapons(dt);
    }
}

void Player::render(std::shared_ptr<sf::RenderWindow> window) {
    if (!explosionPlaying && !deathTimer) {
        weapon.render(window);
        window->draw(sprite);

        if (shieldTimer) {
            sf::Vector2f shieldPosition{sprite.getPosition().x - SHIELD_OFFSET_X, sprite.getPosition().y - SHIELD_OFFSET_Y};
            shield.setPosition(shieldPosition);
            window->draw(shield);
        }

        if (hasShield && !shieldTimer) {
            window->draw(shield);
        }
    } else {
        if (explosionTimer) {
            window->draw(explosion);
        }
    }
}

void Player::shoot() {
    // Randomly picks which side of the top of the players ship to shoot from.
    int tmp{utilities::randomInt(1, 10)};
    if (tmp > 5) {
        shootPosition = sf::Vector2f{position.x + SHOOT_POSITION_OFFSET_LEFT, position.y};
    } else {
        shootPosition = sf::Vector2f{position.x + SHOOT_POSITION_OFFSET_RIGHT, position.y};
    }

    weapon.shoot(shootPosition);
}

void Player::takeShieldDamage(int damage) {
    shieldHealth -= damage;

    if (shieldHealth <= 0) {
        hasShield = false;
    }
}

void Player::kill() {
    explosionPlaying = true;
    createExplosion();
}

void Player::createExplosion() {
    explosion.setPosition(sprite.getPosition());
    explosionTimer = true;

    soundManager.stopSound("bulletHittingPlayerSound");
    soundManager.startSound("biggerExplosionSound", assetManager.getSound("biggerExplosionSound"));
}

void Player::updateWeapons(const float& dt) {
    weapon.update(dt);
    isShootPressed = weapon.getIsShooting();
}

void Player::updateDeathTimer(const float& dt) {
    // Gives time for the death animation to play before going back to the main menu
    if (deathTimer) {
        deathCoolDown -= dt;
        if (deathCoolDown <= TIMER_ZERO) {
            deathTimer = false;
            Character::kill();
        }
    }
}

void Player::updateExplosionTimer(const float& dt) {
    // Displays the explosion animation for a certain amount of time.
    if (explosionTimer) {
        explosionCoolDown -= dt;
        if (explosionCoolDown <= TIMER_ZERO) {
            explosionPlaying = false;
            explosionTimer = false;
            explosionCoolDown = EXPLOSION_COOL_DOWN_TIMER;

            soundManager.stopSound("biggerExplosionSound");
            deathTimer = true;
        }
    }
}

void Player::updateShieldTimer(const float& dt) {
    if (shieldTimer) {
        shieldCoolDown -= dt;
        if (shieldCoolDown <= TIMER_ZERO) {
            shieldPlaying = false;
            shieldCoolDown = false;
            shieldTimer = false;

            // After the animation has played, set the texture to the still shield
            shield.setTexture(assetManager.getTexture("shieldAroundPlayer"));
            sf::Vector2f shieldPosition{sprite.getPosition().x - SHIELD_OFFSET_X, sprite.getPosition().y - SHIELD_OFFSET_Y};
            shield.setPosition(shieldPosition);
        }
    }
}

void Player::getInput(const float& dt) {
    moveDirection.x = input::Input::KeyBoard::getAxis(dt, input::Input::KeyBoard::Axis::Horizontal);

    // TODO Used Input::KeyBoard for shooting input
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && !isShootPressed) {
        isShootPressed = true;
        shoot();
    }
}

void Player::updateAnimations(const float& dt) {
    position = sprite.getPosition();
    checkForSpriteChange();

    // TODO Change this to include both the left and right animations when they are added
    if (!animations.empty()) {
        animations.at(still)->update(dt);
        sprite = animations.at(still)->getSprite();
    }
}

void Player::checkForSpriteChange() {
    if (moveDirection.x < 0.f) {
        moveState = left;
    } else if (moveDirection.x > 0.f) {
        moveState = right;
    } else {
        moveState = still;
    }
}

void Player::initAnimations() {
    explosion.setScale(AssetManager::SPRITE_SCALE_UP_FACTOR, AssetManager::SPRITE_SCALE_UP_FACTOR);

    shield.setScale(AssetManager::SPRITE_SCALE_UP_FACTOR, AssetManager::SPRITE_SCALE_UP_FACTOR);
    shield.setPosition(position);

    sprite.setTexture(assetManager.getTexture("playerShipGrayCenterSheet"));
    sprite.setPosition(position);
    sprite.setScale(AssetManager::SPRITE_SCALE_UP_FACTOR, AssetManager::SPRITE_SCALE_UP_FACTOR);

    // TODO Make Animations for left and right
    // Center
    animations[still] = std::make_unique<Animation>(sprite, 1, 4, Animation::FRAME_DURATION, true);

    // Left

    // Right
}

PlayerWeapon* Player::getWeapon() {
    return &weapon;
}

void Player::updateKillStats(const std::string& enemyKilled) {
    int kills = playerStats.killStats.at(enemyKilled);
    kills++;
    playerStats.killStats.at(enemyKilled) = kills;
}

void Player::checkCollisions() {
    auto enemies{enemyManager->getEnemies()};

    for (const auto& enemy : enemies) {
        auto bullets{enemy->getWeapon()->getBullets()};

        if (!bullets.empty()) {
            for (const auto& bullet : bullets) {
                if (!bullet->isAlive()) {
                    continue;
                }

                sf::FloatRect bulletHitBox{bullet->getHitBox()};

                if (hasShield) {
                    sf::FloatRect shieldHitBox{shield.getGlobalBounds()};

                    if (utilities::checkCollision(bulletHitBox, shieldHitBox)) {
                        bullet->setIsAlive(false);

                        takeShieldDamage(bullet->getDamage());
                        soundManager.startSound("bulletHittingPlayerShieldSound", assetManager.getSound("bulletHittingPlayerShieldSound"));

                        logger.fatal("Player Shield Hit", this);
                        break;
                    }
                } else {
                    sf::FloatRect playerHitBox{getHitBox()};

                    if (utilities::checkCollision(bulletHitBox, playerHitBox)) {
                        bullet->setIsAlive(false);

                        takeDamage(bullet->getDamage());
                        // Play the hit sound when the player gets hit until they are dea, then play the explosion sound
                        if (!isDead()) {
                            soundManager.startSound("bulletHittingPlayerSound", assetManager.getSound("bulletHittingPlayerSound"));
                        }
                        logger.fatal("Player Hit", this);
                        break;
                    }
                }
            }
        }
    }
}

int Player::getShieldHealth() const {
    return shieldHealth;
}

bool Player::getHasShield() const {
    return hasShield;
}

void Player::setHasShield(bool shieldActive) {
    logger.debug("Player shield activated.", this);
    shieldPlaying = true;
    shieldTimer = true;
    hasShield = shieldActive;
}

int Player::getShieldMaxHealth() {
    return MAX_PLAYER_SHIELD_HEALTH;
}

void Player::increaseScore(int scoreAmount) {
    playerStats.score += scoreAmount;
}

Stats Player::getPlayerStats() const {
    return playerStats;
}


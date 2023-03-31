//
// Created by Liam Ross on 25/03/2023.
//

#include "Player.h"

Player::Player(AssetManager& assetManager, SoundManager& soundManager, EnemyManager* enemyManager) noexcept
    : Character{PLAYER_NAME, sf::Vector2f{START_POSITION_X, START_POSITION_Y}, PLAYER_SPEED, assetManager, soundManager},
      moveState{still},
      weapon{assetManager, soundManager},
      score{},
      isShootPressed{false},
      enemyManager{enemyManager}{
    logger.info("Player initialized.", this);
    initAnimations();
    initStats();
}

Player::Player(const sf::Vector2f& position, AssetManager& assetManager, SoundManager& soundManager, EnemyManager* enemyManager) noexcept
    : Character{PLAYER_NAME, position, PLAYER_SPEED, assetManager, soundManager},
      moveState{still},
      weapon{assetManager, soundManager},
      score{},
      isShootPressed{false},
      enemyManager{enemyManager}{
    logger.info("Player initialized.", this);
    initAnimations();
    initStats();
}

Player::Player(const std::string& name, const sf::Vector2f& position, float speed, AssetManager& assetManager, SoundManager& soundManager, EnemyManager* enemyManager) noexcept
    : Character{name, position, speed, assetManager, soundManager},
      moveState{still},
      weapon{assetManager, soundManager},
      score{},
      isShootPressed{false},
      enemyManager{enemyManager} {
    logger.info("Player initialized.", this);
    initAnimations();
    initStats();
}

void Player::update(const float& dt) {
    checkCollisions();
    getInput(dt);
    move(dt, moveDirection.x);

    updateAnimations(dt);
    updateWeapons(dt);
}

void Player::render(std::shared_ptr<sf::RenderWindow> window) {
    weapon.render(window);
    window->draw(sprite);
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

void Player::updateWeapons(const float& dt) {
    weapon.update(dt);
    isShootPressed = weapon.getIsShooting();
}

void Player::getInput(const float& dt) {
    moveDirection.x = input::Input::KeyBoard::getAxis(dt, input::Input::KeyBoard::Axis::Horizontal);

    // TODO Add input checks for shooting
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
    if (moveDirection.x < 0) {
        moveState = left;
    } else if (moveDirection.x > 0) {
        moveState = right;
    } else {
        moveState = still;
    }
}

void Player::initAnimations() {
    sprite.setTexture(assetManager.getTexture("playerShipGrayCenterSheet"));
    sprite.setPosition(position);
    sprite.setScale(AssetManager::SPRITE_SCALE_UP_FACTOR, AssetManager::SPRITE_SCALE_UP_FACTOR);

    // TODO Make Animations for left and right
    // Center
    animations[still] = std::make_unique<Animation>(sprite, 1, 4, Animation::FRAME_DURATION, true);

    // Left

    // Right
}

void Player::initStats() {
    killStats["Blue Enemy"] = 0;
    killStats["Yellow Enemy"] = 0;
    killStats["Green Enemy"] = 0;
    killStats["Purple Enemy"] = 0;
}

PlayerWeapon* Player::getWeapon() {
    return &weapon;
}

void Player::updateKillStats(const std::string& enemyKilled) {
    int kills = killStats.at(enemyKilled);
    kills++;
    killStats.at(enemyKilled) = kills;

//    for (const auto&[enemyName, timesKilled] : killStats) {
//        logger.debug(enemyName + " kills : " + std::to_string(timesKilled));
//    }
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
                sf::FloatRect playerHitBox{getHitBox()};
                if (utilities::checkCollision(bulletHitBox, playerHitBox)) {
                    bullet->setIsAlive(false);
                    takeDamage(bullet->getDamage());
                    logger.fatal("Player Hit", this);
                    break;
                }
            }
        }
    }
}

void Player::increaseScore(int scoreAmount) {
    score += scoreAmount;
}

int Player::getScore() const {
    return score;
}


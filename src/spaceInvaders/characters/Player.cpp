//
// Created by Liam Ross on 25/03/2023.
//

#include "Player.h"

Player::Player(const AssetManager& assetManager, const SoundManager& soundManager) noexcept
    : Character{PLAYER_NAME, sf::Vector2f{START_POSITION_X, START_POSITION_Y}, PLAYER_SPEED, assetManager, soundManager},
      moveState{still},
      score{},
      isShootPressed{false} {
    logger.info("Player initialized.", this);
    initAnimations();
    initWeapon();
}

Player::Player(const sf::Vector2f& position, const AssetManager& assetManager, const SoundManager& soundManager) noexcept
    : Character{PLAYER_NAME, position, PLAYER_SPEED, assetManager, soundManager},
      moveState{still},
      score{},
      isShootPressed{false} {
    logger.info("Player initialized.", this);
    initAnimations();
    initWeapon();
}

Player::Player(const std::string& name, const sf::Vector2f& position, float speed, const AssetManager& assetManager, const SoundManager& soundManager) noexcept
    : Character{name, position, speed, assetManager, soundManager},
      moveState{still},
      score{},
      isShootPressed{false} {
    logger.info("Player initialized.", this);
    initAnimations();
    initWeapon();
}

void Player::update(const float& dt) {
    getInput(dt);
    move(dt, moveDirection.x);

    updateAnimations(dt);
    updateWeapons(dt);
}

void Player::render(std::shared_ptr<sf::RenderWindow> window) {
    weapon->render(window);
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

    weapon->shoot(shootPosition);
}

void Player::updateWeapons(const float& dt) {
    weapon->update(dt);
    isShootPressed = weapon->getIsShooting();
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

void Player::initWeapon() {
    weapon = std::make_unique<PlayerWeapon>(assetManager, soundManager);
}

PlayerWeapon* Player::getWeapon() {
    return weapon.get();
}

void Player::increaseScore(int scoreAmount) {
    score += scoreAmount;
}

int Player::getScore() const {
    return score;
}


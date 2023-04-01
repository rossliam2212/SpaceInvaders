//
// Created by Liam Ross on 30/03/2023.
//

#include "GameStateUI.h"

GameStateUI::GameStateUI(Player* player, AssetManager& assetManager, SoundManager& soundManager) noexcept
    : player{player},
      assetManager{assetManager},
      soundManager{soundManager},
      healthBarValue{},
      shieldBarValue{} {
    initText();
    initSprites();
}

void GameStateUI::update(const float& dt) {
    scoreText.setString("Score: " + std::to_string(player->getPlayerStats().score));

    calculateHealthBarValue();
    healthBarBackground.setSize(sf::Vector2f{BAR_LENGTH * healthBarValue, BAR_HEIGHT});

    calculateShieldBarValue();
    shieldBarBackground.setSize(sf::Vector2f{BAR_LENGTH * shieldBarValue, BAR_HEIGHT});
}

void GameStateUI::render(std::shared_ptr<sf::RenderWindow> window) {
    window->draw(scoreText);

    window->draw(heartIcon);
    window->draw(healthBarBackground);
    window->draw(healthBar);

    window->draw(shieldIcon);
    if (player->getHasShield()) {
        window->draw(shieldBarBackground);
    }
    window->draw(shieldBar);
}

void GameStateUI::calculateHealthBarValue() {
    healthBarValue = (float)player->getHealth() / (float)Player::getMaxHealth();
}

void GameStateUI::calculateShieldBarValue() {
    shieldBarValue = (float)player->getShieldHealth() / (float)Player::getShieldMaxHealth();
}

void GameStateUI::initText() {
    scoreText.setCharacterSize(50);
    scoreText.setPosition(sf::Vector2f{100.f, 35.f});
    scoreText.setFont(assetManager.getFont("PixelFont"));
    scoreText.setFillColor(assetManager.getColor("white"));
}

void GameStateUI::initSprites() {
    heartIcon.setTexture(assetManager.getTexture("heartIcon"));
    heartIcon.setPosition(sf::Vector2f{500.f, UI_Y_POS});
    heartIcon.setScale(AssetManager::SPRITE_SCALE_UP_FACTOR, AssetManager::SPRITE_SCALE_UP_FACTOR);

    healthBar.setTexture(assetManager.getTexture("barWhite"));
    healthBar.setPosition(sf::Vector2f{575.f, UI_Y_POS});
    healthBar.setScale(AssetManager::SPRITE_SCALE_UP_FACTOR, AssetManager::SPRITE_SCALE_UP_FACTOR);

    healthBarBackground.setPosition(585.f, UI_Y_POS);
    healthBarBackground.setSize(sf::Vector2f{BAR_LENGTH, BAR_HEIGHT});
    healthBarBackground.setFillColor(assetManager.getColor("healthBarColor"));

    shieldIcon.setTexture(assetManager.getTexture("shieldIcon"));
    shieldIcon.setPosition(sf::Vector2f{900.f, UI_Y_POS});
    shieldIcon.setScale(AssetManager::SPRITE_SCALE_UP_FACTOR, AssetManager::SPRITE_SCALE_UP_FACTOR);

    shieldBar.setTexture(assetManager.getTexture("barWhite"));
    shieldBar.setPosition(sf::Vector2f{975.f, UI_Y_POS});
    shieldBar.setScale(AssetManager::SPRITE_SCALE_UP_FACTOR, AssetManager::SPRITE_SCALE_UP_FACTOR);

    shieldBarBackground.setPosition(985.f, UI_Y_POS);
    shieldBarBackground.setSize(sf::Vector2f{BAR_LENGTH, BAR_HEIGHT});
    shieldBarBackground.setFillColor(assetManager.getColor("shieldBarColor"));
}
//
// Created by Liam Ross on 21/03/2023.
//

#include "MainMenuState.h"

MainMenuState::MainMenuState(const std::shared_ptr<sf::RenderWindow>& window, std::stack<std::unique_ptr<State>>& states, const AssetManager& assetManager, const SoundManager& soundManager) noexcept
    : State(window, states, assetManager, soundManager) {
    initBackground();
    initSprites();
    initText();
}

void MainMenuState::update(const float& dt) {
    updateMousePositions();
}

void MainMenuState::updateInput(const float& dt) {

}

void MainMenuState::render(std::shared_ptr<sf::RenderWindow> window) {
    window->draw(backGround);
    window->draw(logoSprite);
    window->draw(startText);
}

void MainMenuState::initBackground() {
    backGround.setSize(sf::Vector2f{static_cast<float>(window->getSize().x), static_cast<float>(window->getSize().y)});
    backGround.setFillColor(assetManager.getColor("mainMenuBackgroundColor"));
}

void MainMenuState::initSprites() {
    logoSprite.setTexture(assetManager.getTexture("mainMenuLogo"));
    sf::Vector2f spriteSize(logoSprite.getGlobalBounds().width, logoSprite.getGlobalBounds().height);
    logoSprite.setOrigin(spriteSize.x / 2, spriteSize.y / 2);
    logoSprite.setPosition(sf::Vector2f{static_cast<float>(window->getSize().x/2), static_cast<float>(window->getSize().y/2.f)});
}

void MainMenuState::initText() {
    startText.setPosition(500, 1100);
    startText.setString("Press Start");
    startText.setCharacterSize(70);
    startText.setFont(assetManager.getFont("BlueSmileFont"));
}


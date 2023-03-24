//
// Created by Liam Ross on 21/03/2023.
//

#include "MainMenuState.h"

MainMenuState::MainMenuState(const std::shared_ptr<sf::RenderWindow>& window, std::stack<std::unique_ptr<State>>& states, const AssetManager& assetManager, const SoundManager& soundManager) noexcept
    : State(window, states, assetManager, soundManager) {
    initBackground();
    initSprites();
    initText();
    initButtons();
}

void MainMenuState::update(const float& dt) {
    updateMousePositions();
    updateButtons();
}

void MainMenuState::updateInput(const float& dt) {

}

void MainMenuState::render(std::shared_ptr<sf::RenderWindow> window) {
    window->draw(backGround);
    window->draw(logoSprite);
//    window->draw(startText);

    renderButtons(window);

}

void MainMenuState::updateButtons() {
    startButton->update(mousePosView);

    if (startButton->isPressed() && !startPressed) {
        logger.info("Start button pressed.", this);
        startPressed = true;
    }
}

void MainMenuState::renderButtons(std::shared_ptr<sf::RenderWindow> window) {
    if (startButton->getShouldDisplay()) {
        startButton->render(window);
    }
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
    // TODO Change hard coded values
    startText.setPosition(500, 1100);
    startText.setString("Press Start");
    startText.setCharacterSize(AssetManager::FONT_HEADING_2);
    startText.setFont(assetManager.getFont("BlueSmileFont"));
}

void MainMenuState::initButtons() {
    startButton = std::make_unique<Button>(500, 1100, 500, 100, assetManager.getFont("BlueSmileFont"), AssetManager::FONT_HEADING_2, "Press Start", sf::Color{0, 0, 0, 0}, sf::Color{50, 50, 50, 255}, sf::Color::White, true);
}


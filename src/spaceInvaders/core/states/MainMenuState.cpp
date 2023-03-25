//
// Created by Liam Ross on 21/03/2023.
//

#include "MainMenuState.h"

MainMenuState::MainMenuState(const std::shared_ptr<sf::RenderWindow>& window, std::stack<std::unique_ptr<State>>& states, const std::unordered_map<std::string, int>& supportedKeys, const AssetManager& assetManager, const SoundManager& soundManager) noexcept
    : State(window, states, supportedKeys, assetManager, soundManager) {
    initBackground();
    initSprites();
    initText();
    initButtons();
}

void MainMenuState::update(const float& dt) {
    updateMousePositions();
    updateButtons();
}

void MainMenuState::render(std::shared_ptr<sf::RenderWindow> window) {
    window->draw(backGround);
    window->draw(logoSprite);

    renderButtons(window);
}

void MainMenuState::updateButtons() {
    for (const auto& btn : buttons) {
        btn.second->update(mousePosView);
    }

    if (buttons.at("startBtn")->isPressed() && !startPressed) {
        logger.info("Starting GameState.", this);
        states.push(std::make_unique<GameState>(window, states, supportedKeys, assetManager, soundManager));
        startPressed = true;
    }

    if (buttons.at("quitBtn")->isPressed()) {
        logger.info("Ending state.", this);
        startPressed = true;
        endState();
    }
}

void MainMenuState::renderButtons(const std::shared_ptr<sf::RenderWindow>& window) {
    for (const auto& btn : buttons) {
        if (btn.second->getShouldDisplay()) {
            btn.second->render(window);
        }
    }
}

void MainMenuState::initBackground() {
    backGround.setSize(sf::Vector2f{static_cast<float>(window->getSize().x), static_cast<float>(window->getSize().y)});
    backGround.setFillColor(assetManager.getColor("mainMenuBackgroundColor"));
}

void MainMenuState::initSprites() {
    logoSprite.setTexture(assetManager.getTexture("mainMenuLogoPixel"));
    sf::Vector2f spriteSize(logoSprite.getGlobalBounds().width, logoSprite.getGlobalBounds().height);
    logoSprite.setOrigin(spriteSize.x / 2, spriteSize.y / 2);
    logoSprite.setPosition(sf::Vector2f{static_cast<float>(window->getSize().x/2), static_cast<float>(window->getSize().y/2.f)});
}

void MainMenuState::initText() { }

void MainMenuState::initButtons() {
    buttons["startBtn"] = std::make_unique<Button>(350, 1100, 300, 100, assetManager.getFont("PixelFont"), AssetManager::FONT_HEADING_2, "Start", assetManager.getColor("transparent"), assetManager.getColor("btnHoverLightGray"), assetManager.getColor("white"), true);
    buttons["quitBtn"] = std::make_unique<Button>(850, 1100, 300, 100, assetManager.getFont("PixelFont"), AssetManager::FONT_HEADING_2, "Quit", assetManager.getColor("transparent"), assetManager.getColor("btnHoverLightGray"), assetManager.getColor("white"), true);
}


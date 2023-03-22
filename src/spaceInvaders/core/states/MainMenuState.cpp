//
// Created by Liam Ross on 21/03/2023.
//

#include "MainMenuState.h"

MainMenuState::MainMenuState(const std::shared_ptr<sf::RenderWindow>& window, std::stack<std::unique_ptr<State>>& states, const AssetManager& assetManager) noexcept
    : State(window, states, assetManager) {
    initBG();
}

void MainMenuState::update(const float& dt) {
    updateMousePositions();
}

void MainMenuState::updateInput(const float& dt) {

}

void MainMenuState::render(std::shared_ptr<sf::RenderWindow> window) {
    window->draw(bg);
}

void MainMenuState::initBG() {
    bg.setSize(sf::Vector2f{static_cast<float>(window->getSize().x), static_cast<float>(window->getSize().y)});
    bg.setFillColor(sf::Color{40, 40, 40, 255});
}

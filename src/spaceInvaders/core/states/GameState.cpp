//
// Created by Liam Ross on 25/03/2023.
//

#include "GameState.h"

GameState::GameState(const std::shared_ptr<sf::RenderWindow>& window, std::stack<std::unique_ptr<State>>& states, const AssetManager& assetManager, const SoundManager& soundManager) noexcept
    : State(window, states, assetManager, soundManager) {
}

void GameState::update(const float& dt) {

}

void GameState::updateInput(const float& dt) { }

void GameState::render(std::shared_ptr<sf::RenderWindow> window) {

}

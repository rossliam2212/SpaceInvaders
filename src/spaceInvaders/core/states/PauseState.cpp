//
// Created by Liam Ross on 04/04/2023.
//

#include "PauseState.h"

PauseState::PauseState(const std::shared_ptr<sf::RenderWindow>& window, std::stack<std::unique_ptr<State>>& states, const std::unordered_map<std::string, int>& supportedKeys, AssetManager& assetManager, SoundManager& soundManager) noexcept
    : State{window, states, supportedKeys, assetManager, soundManager} {
    pauseState();
    initBackground();
}

void PauseState::update(const float& dt) {
    if (isPaused()) {
        updateMousePositions();
    }
}

void PauseState::render(std::shared_ptr<sf::RenderWindow> window) {

}

void PauseState::initBackground() {

}
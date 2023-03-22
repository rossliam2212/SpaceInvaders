//
// Created by Liam Ross on 21/03/2023.
//

#include "State.h"

State::State(const std::shared_ptr<sf::RenderWindow>& window, std::stack<std::unique_ptr<State>>& states, const AssetManager& assetManager, const SoundManager& soundManager) noexcept
    : window{window},
      states{states},
      assetManager{assetManager},
      soundManager{soundManager},
      end{false},
      logger{"logs"} {
    input::Input::Mouse::init(window.get());
}

void State::updateMousePositions() {
    mousePosScreen = input::Input::Mouse::getPosition();
    mousePosWindow = input::Input::Mouse::getRelativePosition();
    mousePosView = input::Input::Mouse::getRelativeCoords();
}

void State::endState() {
    end = true;
}

bool State::getEnd() const {
    return end;
}

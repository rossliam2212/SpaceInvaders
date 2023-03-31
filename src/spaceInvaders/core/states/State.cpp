//
// Created by Liam Ross on 21/03/2023.
//

#include "State.h"

State::State(const std::shared_ptr<sf::RenderWindow>& window, std::stack<std::unique_ptr<State>>& states, const std::unordered_map<std::string, int>& supportedKeys, AssetManager& assetManager, SoundManager& soundManager) noexcept
    : window{window},
      states{states},
      supportedKeys{supportedKeys},
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

void State::delayForMilliseconds(int milliseconds) {
    if (milliseconds <= 0) {
//        logger.error("Cannot delay for 0 or negative milliseconds!", this);
        return;
    }
    std::chrono::milliseconds mills{std::chrono::milliseconds{milliseconds}};
    std::this_thread::sleep_for(mills);
}

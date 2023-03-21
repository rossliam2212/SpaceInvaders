//
// Created by Liam Ross on 21/03/2023.
//

#include "State.h"

State::State(sf::RenderWindow& window, std::stack<std::unique_ptr<State>>& states) noexcept
    : window{window},
      states{states},
      end{false},
      logger{"logs"} {
    input::Input::Mouse::init(&window);
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

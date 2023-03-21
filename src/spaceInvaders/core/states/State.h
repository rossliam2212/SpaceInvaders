//
// Created by Liam Ross on 21/03/2023.
//

#ifndef SPACE_INVADERS_STATE_H
#define SPACE_INVADERS_STATE_H

#include <SFML/Graphics.hpp>
#include <Logger.h>
#include <stack>
#include <memory>

#include "../../input/Input.h"


class State {
protected:
    sf::RenderWindow& window;
    std::stack<std::unique_ptr<State>>& states;
    bool end;

    sf::Vector2f mousePosWindow;
    sf::Vector2f mousePosScreen;
    sf::Vector2f mousePosView;

    logger::Logger logger;

public:
    State(sf::RenderWindow& window, std::stack<std::unique_ptr<State>>& states) noexcept;

    virtual void update() = 0;
    virtual void updateInput(const float& dt) = 0;
    virtual void render(sf::RenderWindow& window) = 0;

    void endState();
    bool getEnd() const;

protected:
    void updateMousePositions();
};


#endif //SPACE_INVADERS_STATE_H

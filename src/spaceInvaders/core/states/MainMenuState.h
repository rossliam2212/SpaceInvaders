//
// Created by Liam Ross on 21/03/2023.
//

#ifndef SPACE_INVADERS_MAINMENUSTATE_H
#define SPACE_INVADERS_MAINMENUSTATE_H

#include "State.h"

class MainMenuState : public State {
private:
    sf::RectangleShape bg; // TODO Temporary - REMOVE

public:
    MainMenuState(const std::shared_ptr<sf::RenderWindow>& window, std::stack<std::unique_ptr<State>>& states) noexcept;
    ~MainMenuState() override = default;

    void update(const float& dt) override;
    void updateInput(const float& dt) override;
    void render(std::shared_ptr<sf::RenderWindow> window) override;

private:
    void initBG(); // TODO Temporary - REMOVE
};


#endif //SPACE_INVADERS_MAINMENUSTATE_H

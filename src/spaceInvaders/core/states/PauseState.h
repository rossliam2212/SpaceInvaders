//
// Created by Liam Ross on 04/04/2023.
//

#ifndef SPACE_INVADERS_PAUSESTATE_H
#define SPACE_INVADERS_PAUSESTATE_H

#include "State.h"

class PauseState : public State {
private:
    sf::RectangleShape backGround;

public:
    PauseState(const std::shared_ptr<sf::RenderWindow>& window, std::stack<std::unique_ptr<State>>& states,
               const std::unordered_map<std::string, int>& supportedKeys, AssetManager& assetManager,
               SoundManager& soundManager) noexcept;
    ~PauseState() override = default;

    void update(const float& dt) override;
    void render(std::shared_ptr<sf::RenderWindow> window) override;

private:
    void initBackground();
};


#endif //SPACE_INVADERS_PAUSESTATE_H

//
// Created by Liam Ross on 25/03/2023.
//

#ifndef SPACE_INVADERS_GAMESTATE_H
#define SPACE_INVADERS_GAMESTATE_H

#include "State.h"

class GameState : public State {
private:

public:
    GameState(const std::shared_ptr<sf::RenderWindow>& window, std::stack<std::unique_ptr<State>>& states,
          const AssetManager& assetManager, const SoundManager& soundManager) noexcept;
    ~GameState() override = default;

    void update(const float& dt) override;
    void updateInput(const float& dt) override;
    void render(std::shared_ptr<sf::RenderWindow> window) override;

};


#endif //SPACE_INVADERS_GAMESTATE_H

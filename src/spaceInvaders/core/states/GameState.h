//
// Created by Liam Ross on 25/03/2023.
//

#ifndef SPACE_INVADERS_GAMESTATE_H
#define SPACE_INVADERS_GAMESTATE_H

#include "State.h"
#include "../../managers/EnemyManager.h"
#include "../../managers/ObjectManager.h"
#include "../../ui/GameStateUI.h"

class GameState : public State {
private:
    static constexpr const char* GAME_STATE_KEY_BINDS{"../config/gameStateKeyBinds.ini"};
    Player player;
    EnemyManager enemyManager;
    ObjectManager objectManager;

    GameStateUI ui;

public:
    GameState(const std::shared_ptr<sf::RenderWindow>& window, std::stack<std::unique_ptr<State>>& states,
              const std::unordered_map<std::string, int>& supportedKeys, AssetManager& assetManager,
              SoundManager& soundManager) noexcept;
    ~GameState() override = default;

    void update(const float& dt) override;
    void render(std::shared_ptr<sf::RenderWindow> window) override;

private:
    void initKeyBinds();
};


#endif //SPACE_INVADERS_GAMESTATE_H

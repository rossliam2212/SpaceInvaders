//
// Created by Liam Ross on 25/03/2023.
//

#include "GameState.h"

GameState::GameState(const std::shared_ptr<sf::RenderWindow>& window, std::stack<std::unique_ptr<State>>& states, const std::unordered_map<std::string, int>& supportedKeys, AssetManager& assetManager, SoundManager& soundManager) noexcept
    : State(window, states, supportedKeys, assetManager, soundManager),
      player{assetManager, soundManager, &enemyManager},
      enemyManager{&player, assetManager, soundManager},
      ui{&player, assetManager, soundManager} {
    initKeyBinds();
}

void GameState::update(const float& dt) {
    player.update(dt);
    enemyManager.update(dt);
    ui.update(dt);

    if (player.isDead()) {
        logger.info("Player killed!", this);
        logger.info("Ending state.", this);
        endState();
    }
}

void GameState::render(std::shared_ptr<sf::RenderWindow> window) {
    player.render(window);
    enemyManager.render(window);
    ui.render(window);
}

void GameState::initKeyBinds() {
    std::ifstream gameStateKeyBindsConfig{GAME_STATE_KEY_BINDS};

    if (!gameStateKeyBindsConfig.is_open()) {
        logger.error("Failed to open key binds config.", this);
        std::exit(-1);
    }

    if (utilities::isFileEmpty(gameStateKeyBindsConfig)) {
        logger.error("Key binds config empty.", this);
        std::exit(-1);
    } else {
        try {
            std::string action;
            std::string key;

            while (gameStateKeyBindsConfig >> action >> key) {
                keyBinds[action] = supportedKeys.at(key);
            }
            logger.info("Successfully initialized key binds.", this);
        } catch (const std::exception& ex) {
            std::string exception{ex.what()};
            logger.error("Exception caught: " + exception, this);
        }
    }
    gameStateKeyBindsConfig.close();

    input::Input::KeyBoard::init(&supportedKeys, &keyBinds);
}

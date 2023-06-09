//
// Created by Liam Ross on 25/03/2023.
//

#include "GameState.h"

GameState::GameState(const std::shared_ptr<sf::RenderWindow>& window, std::stack<std::unique_ptr<State>>& states, const std::unordered_map<std::string, int>& supportedKeys, AssetManager& assetManager, SoundManager& soundManager) noexcept
    : State(window, states, supportedKeys, assetManager, soundManager),
      player{assetManager, soundManager, &enemyManager},
      enemyManager{&player, assetManager, soundManager},
      objectManager{&player, &enemyManager, assetManager, soundManager},
      ui{&player, assetManager, soundManager} {
    initKeyBinds();
}

void GameState::update(const float& dt) {
    // TODO Move to separate function
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape) && !isPaused()) {
        logger.info("Starting PauseState.", this, __LINE__);
        logger.debug("Game paused.", this, __LINE__);
        pauseState();
        states.push(std::make_unique<PauseState>(window, states, supportedKeys, assetManager, soundManager));
    }

    if (!isPaused()) {
        if (!enemyManager.allEnemiesDead()) {
            player.update(dt);
            enemyManager.update(dt);
            objectManager.update(dt);
            ui.update(dt);

            if (player.isDead()) {
                logger.debug("Player killed!", this, __LINE__);
                logger.info("Ending state.", this, __LINE__);
                endState();
            }
        } else {
            enemyManager.reset();
            enemyManager.initEnemies();
        }
    }
}

void GameState::render(std::shared_ptr<sf::RenderWindow> window) {
    player.render(window);
    enemyManager.render(window);
    objectManager.render(window);
    ui.render(window);
}

void GameState::initKeyBinds() {
    std::ifstream gameStateKeyBindsConfig{GAME_STATE_KEY_BINDS};

    if (!gameStateKeyBindsConfig.is_open()) {
        logger.error("Failed to open key binds config.", this, __LINE__);
        std::exit(-1);
    }

    if (utilities::isFileEmpty(gameStateKeyBindsConfig)) {
        logger.error("Key binds config empty.", this, __LINE__);
        std::exit(-1);
    } else {
        try {
            std::string action;
            std::string key;

            while (gameStateKeyBindsConfig >> action >> key) {
                keyBinds[action] = supportedKeys.at(key);
            }
            logger.info("Successfully initialized key binds.", this, __LINE__);
        } catch (const std::exception& ex) {
            std::string exception{ex.what()};
            logger.error("Exception caught: " + exception, this, __LINE__);
        }
    }
    gameStateKeyBindsConfig.close();

    input::Input::KeyBoard::init(&supportedKeys, &keyBinds);
}

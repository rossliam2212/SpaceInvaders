//
// Created by Liam Ross on 21/03/2023.
//

#ifndef SPACE_INVADERS_STATE_H
#define SPACE_INVADERS_STATE_H

#include <SFML/Graphics.hpp>
#include <Logger.h>
#include <array>
#include <stack>
#include <map>
#include <unordered_map>
#include <memory>
#include <fstream>
#include <algorithm>
#include <chrono>
#include <thread>

#include "../../managers/AssetManager.h"
#include "../../managers/SoundManager.h"
#include "../../input/Input.h"
#include "../../ui/Button.h"


class State {
protected:
    std::shared_ptr<sf::RenderWindow> window;
    std::stack<std::unique_ptr<State>>& states;
    std::unordered_map<std::string, int> supportedKeys;
    std::unordered_map<std::string, int> keyBinds;
    AssetManager assetManager;
    SoundManager soundManager;
    bool end;

    sf::Vector2f mousePosWindow;
    sf::Vector2f mousePosScreen;
    sf::Vector2f mousePosView;

    logger::Logger logger;

public:
    State(const std::shared_ptr<sf::RenderWindow>& window, std::stack<std::unique_ptr<State>>& states,
          const std::unordered_map<std::string, int>& supportedKeys, const AssetManager& assetManager,
          const SoundManager& soundManager) noexcept;
    virtual ~State() = default;

    virtual void update(const float& dt) = 0;
    virtual void updateInput(const float& dt) = 0;
    virtual void render(std::shared_ptr<sf::RenderWindow> window) = 0;

    void endState();
    bool getEnd() const;
    static void delayForMilliseconds(int milliseconds);

protected:
    void updateMousePositions();
};


#endif //SPACE_INVADERS_STATE_H

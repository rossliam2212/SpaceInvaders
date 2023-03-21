//
// Created by Liam Ross on 21/03/2023.
//

#ifndef SPACE_INVADERS_APPLICATION_H
#define SPACE_INVADERS_APPLICATION_H

#include <Logger.h>

#include "states/State.h"
#include "../utilities/FixedClock.h"

class Application {
private:
    sf::RenderWindow window;
    sf::Event event;

    std::stack<std::unique_ptr<State>> states;
    std::map<std::string, int> supportedKeys;

    FixedClock dtClock;
    float deltaTime;

    logger::Logger logger;

public:
    Application() noexcept;
    ~Application() = default;

    void run();

private:
    void update();
    void render();
    void updateDeltaClock();
    void updateEvents();

    void endApplication();

    void initWindow();
    void initStates();
    void initKeys();
};


#endif //SPACE_INVADERS_APPLICATION_H

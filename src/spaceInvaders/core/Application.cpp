//
// Created by Liam Ross on 21/03/2023.
//

#include "Application.h"

Application::Application() noexcept
    : window{},
      event{},
      states{},
      supportedKeys{},
      dtClock{true},
      deltaTime{},
      logger{"logs"} {
    logger.start("Application starting.", this, __LINE__);

    initWindow();
    initKeys();
    initStates();
}

void Application::run() {
    while (window->isOpen()) {
        render();
        update();
    }
}

void Application::update() {
    updateDeltaClock();
    updateEvents();

    if (!states.empty()) {
        states.top()->update(deltaTime);

        if (states.top()->getEnd()) {
            states.pop();
        }
    } else {
        endApplication();
    }
}

void Application::render() {
    window->clear();

    if (!states.empty())
        states.top()->render(window);

    window->display();
}

void Application::updateDeltaClock() {
    dtClock.stop();
    deltaTime = dtClock.GetElapsedTime().asSeconds();
    dtClock.start();
}

void Application::updateEvents() {
    while (window->pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            endApplication();
        }
    }
}

void Application::endApplication() {
    window->close();
    logger.info("Logs written to: '" + logger.getWhereLogged() + "'", this, __LINE__);
    logger.end("Application ended.", this, __LINE__);
    logger.info("==================================================================================", this, __LINE__);
}

void Application::initWindow() {
    // TODO Create window config file to store all of the windows details
    logger.info("Window initialized.", this, __LINE__);
    window = std::make_shared<sf::RenderWindow>(sf::VideoMode{WINDOW_WIDTH, WINDOW_HEIGHT}, "Space Invaders", sf::Style::Titlebar | sf::Style::Close);
}

void Application::initStates() {
    logger.info("Starting LoadingGameState.", this, __LINE__);
    states.push(std::make_unique<LoadingGameState>(window, states, supportedKeys, assetManager, soundManager));
}

void Application::initKeys() {
    std::ifstream in{SUPPORTED_KEYS_CONFIG};

    if (!in.is_open()) {
        logger.error("Failed to open supported keys config file.", this, __LINE__);
        std::exit(-1);
    }

    try {
        std::string key; // The key
        int keyValue; // The key value

        while (in >> key >> keyValue) {
            supportedKeys[key] = keyValue;
        }
        logger.info("Successfully initialized supported keys.", this, __LINE__);
    } catch (const std::exception& ex) {
        std::string exception{ex.what()};
        logger.error("Exception caught: " + exception, this, __LINE__);
    }
    in.close();
}
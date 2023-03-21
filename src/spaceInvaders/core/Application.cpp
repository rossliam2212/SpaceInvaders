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
    logger.start("Application starting.", this);

    initWindow();
    initStates();
    initKeys();
    initAssets();
}

void Application::run() {
    while (window->isOpen()) {
        update();
        render();
    }
}

void Application::update() {
    updateDeltaClock();
    updateEvents();

    if (!states.empty()) {
        states.top()->update();

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
    logger.info("Logs written to: '" + logger.getWhereLogged() + "'", this);
    logger.end("Application ended.", this);
    logger.info("==================================================================================", this);
}

void Application::initWindow() {
    logger.info("Window initialized.", this);
    window = std::make_shared<sf::RenderWindow>(sf::VideoMode{WINDOW_WIDTH, WINDOW_HEIGHT}, "Minesweeper", sf::Style::Titlebar | sf::Style::Close);
}

void Application::initStates() {
    logger.info("Starting MainMenuState.", this);
//    states.push(std::make_unique<MainMenuState>());
}

void Application::initKeys() {
    std::ifstream in{"../config/supportedKeys.ini"};

    if (!in.is_open()) {
        logger.error("Failed to open supported keys config file.", this);
        std::exit(-1);
    }

    try {
        std::string key; // The key
        int keyValue; // The key value

        while (in >> key >> keyValue) {
            supportedKeys[key] = keyValue;
        }
    } catch (const std::exception& ex) {
        std::string exception{ex.what()};
        logger.error("Exception caught: " + exception);
    }
    in.close();
}


void Application::initAssets() {
    // TODO Create assets config file to read in all the assets
}

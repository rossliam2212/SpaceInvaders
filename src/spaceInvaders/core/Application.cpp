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
}

void Application::run() {
    while (window.isOpen()) {
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
    window.clear();

    if (!states.empty())
        states.top()->render(window);

    window.display();
}

void Application::updateDeltaClock() {
    dtClock.stop();
    deltaTime = dtClock.GetElapsedTime().asSeconds();
    dtClock.start();
}

void Application::updateEvents() {
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            endApplication();
        }
    }
}

void Application::endApplication() {
    window.close();
    logger.info("Logs written to: '" + logger.getWhereLogged() + "'", this);
    logger.end("Application ended.", this);
    logger.info("==================================================================================", this);
}

void Application::initWindow() {

}

void Application::initStates() {

}

void Application::initKeys() {

}

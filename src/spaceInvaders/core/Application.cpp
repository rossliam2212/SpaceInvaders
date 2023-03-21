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

    initAssets();
    initKeys();
    initWindow();
    initStates();
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
    logger.info("Logs written to: '" + logger.getWhereLogged() + "'", this);
    logger.end("Application ended.", this);
    logger.info("==================================================================================", this);
}

void Application::initWindow() {
    // TODO Create window config file to store all of the windows details
    logger.info("Window initialized.", this);
    window = std::make_shared<sf::RenderWindow>(sf::VideoMode{WINDOW_WIDTH, WINDOW_HEIGHT}, "Space Invaders", sf::Style::Titlebar | sf::Style::Close);
}

void Application::initStates() {
    logger.info("Starting MainMenuState.", this);
    states.push(std::make_unique<MainMenuState>(window, states));
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
        logger.info("Successfully initialized supported keys.", this);
    } catch (const std::exception& ex) {
        std::string exception{ex.what()};
        logger.error("Exception caught: " + exception);
    }
    in.close();
}


void Application::initAssets() {
    logger.info("Loading assets...", this);

    // Loading Fonts
    std::ifstream fonts{"../config/fontAssets.ini"};

    if (utilities::isFileEmpty(fonts)) {
        logger.warning("Font assets config file empty. Skipping...", this);
    } else {
        if (!fonts.is_open()) {
            logger.error("Failed to open font assets config file.", this);
            std::exit(-1);
        }

        try {
            std::string assetName;
            std::string assetLocation;

            while (fonts >> assetName >> assetLocation) {
                assetManager.loadFont(assetName, assetLocation);
            }
            logger.info("Successfully loaded fonts.", this);
        } catch (const std::exception& ex) {
            std::string exception{ex.what()};
            logger.error("Exception caught: " + exception);
        }
        fonts.close();
    }


    // Loading Textures
    std::ifstream textures{"../config/textureAssets.ini"};

    if (utilities::isFileEmpty(textures)) {
        logger.warning("Texture assets config file empty. Skipping...", this);
    } else {
        if (!textures.is_open()) {
            logger.error("Failed to open texture assets config file.", this);
            std::exit(-1);
        }

        try {
            std::string assetName;
            std::string assetLocation;

            while (textures >> assetName >> assetLocation) {
                assetManager.loadTexture(assetName, assetLocation);
            }
            logger.info("Successfully loaded textures.", this);
        } catch (const std::exception& ex) {
            std::string exception{ex.what()};
            logger.error("Exception caught: " + exception, this);
        }
        textures.close();
    }

    // Loading Sounds
    std::ifstream sounds{"../config/soundAssets.ini"};

    if (utilities::isFileEmpty(sounds)) {
        logger.warning("Sound assets config file empty. Skipping...", this);
    } else {
        if (!sounds.is_open()) {
            logger.error("Failed to open sound assets config file.", this);
            std::exit(-1);
        }

        try {
            std::string assetName;
            std::string assetLocation;

            while (sounds >> assetName >> assetLocation) {
                assetManager.loadTexture(assetName, assetLocation);
            }
            logger.info("Successfully loaded sounds.", this);
        } catch (const std::exception& ex) {
            std::string exception{ex.what()};
            logger.error("Exception caught: " + exception, this);
        }
        sounds.close();
    }
}

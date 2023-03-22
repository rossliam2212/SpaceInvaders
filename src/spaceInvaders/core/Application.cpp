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
    soundManager.startSound("badHabit", assetManager.getSound("badHabit"));
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

        // TODO Testing Sound - REMOVE
        if (event.type == sf::Event::KeyPressed) {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) {
                soundManager.pauseSound("badHabit");
            }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) {
                soundManager.playSound("badHabit");
            }
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
    states.push(std::make_unique<MainMenuState>(window, states, assetManager, soundManager));
}

void Application::initKeys() {
    std::ifstream in{SUPPORTED_KEYS_CONFIG};

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

    initFontAssets();
    initTextureAssets();
    initSoundAssets();
    initColorAssets();
}

void Application::initFontAssets() {
    std::ifstream fonts{FONT_ASSETS_CONFIG};

    if (!fonts.is_open()) {
        logger.error("Failed to open font assets config file.", this);
        std::exit(-1);
    }

    if (utilities::isFileEmpty(fonts)) {
        logger.warning("Font assets config file empty. Skipping...", this);
    } else {
        try {
            std::string fontName;
            std::string fontPath;

            while (fonts >> fontName >> fontPath) {
                assetManager.loadFont(fontName, fontPath);
            }
            logger.info("Successfully loaded fonts.", this);
        } catch (const std::exception& ex) {
            std::string exception{ex.what()};
            logger.error("Exception caught: " + exception);
        }
        fonts.close();
    }
}

void Application::initTextureAssets() {
    std::ifstream textures{TEXTURE_ASSETS_CONFIG};

    if (!textures.is_open()) {
        logger.error("Failed to open texture assets config file.", this);
        std::exit(-1);
    }

    if (utilities::isFileEmpty(textures)) {
        logger.warning("Texture assets config file empty. Skipping...", this);
    } else {
        try {
            std::string textureName;
            std::string texturePath;

            while (textures >> textureName >> texturePath) {
                assetManager.loadTexture(textureName, texturePath);
            }
            logger.info("Successfully loaded textures.", this);
        } catch (const std::exception& ex) {
            std::string exception{ex.what()};
            logger.error("Exception caught: " + exception, this);
        }
        textures.close();
    }
}

void Application::initSoundAssets() {
    std::ifstream sounds{SOUND_ASSETS_CONFIG};

    if (!sounds.is_open()) {
        logger.error("Failed to open sound assets config file.", this);
        std::exit(-1);
    }

    if (utilities::isFileEmpty(sounds)) {
        logger.warning("Sound assets config file empty. Skipping...", this);
    } else {
        try {
            std::string soundName;
            std::string soundPath;

            while (sounds >> soundName >> soundPath) {
                assetManager.loadSound(soundName, soundPath);
            }
            logger.info("Successfully loaded sounds.", this);
        } catch (const std::exception& ex) {
            std::string exception{ex.what()};
            logger.error("Exception caught: " + exception, this);
        }
        sounds.close();
    }
}

void Application::initColorAssets() {
    std::ifstream colors{COLOR_ASSETS_CONFIG};

    if (!colors.is_open()) {
        logger.error("Failed to open color assets config file.", this);
        std::exit(-1);
    }

    if (utilities::isFileEmpty(colors)) {
        logger.warning("Color assets config file empty. Skipping...", this);
    } else {
        try {
            std::string colorName;
            sf::Uint8 r;
            sf::Uint8 g;
            sf::Uint8 b;
            sf::Uint8 alpha;

            while (colors >> colorName >> r >> g >> b >> alpha) {
                assetManager.loadColor(colorName, sf::Color{r, g, b, alpha});
            }
            logger.info("Successfully loaded colors.", this);
        } catch (const std::exception& ex) {
            std::string exception{ex.what()};
            logger.error("Exception caught: " + exception, this);
        }
        colors.close();
    }
}

//
// Created by Liam Ross on 23/03/2023.
//

#include "LoadingGameState.h"

LoadingGameState::LoadingGameState(const std::shared_ptr<sf::RenderWindow>& window, std::stack<std::unique_ptr<State>>& states, const std::unordered_map<std::string, int>& supportedKeys, AssetManager& assetManager, SoundManager& soundManager) noexcept
    : State(window, states, supportedKeys, assetManager, soundManager),
      progress{0.f},
      backGroundColor{sf::Color{43, 43, 43, 255}},
      assets{},
      loadNextState{false},
      allAssetsLoaded{false} {
    initBackground();
    initFont();
    initText();
    initProgressBar();
    initAssets();
}

void LoadingGameState::update(const float& dt) {
    if (!checkIfAllAssetsLoaded()) {
        for (auto& asset : assets) {
            loadAsset(asset);
        }
    } else {
        if (!loadNextState) {
            setAllAssetsLoaded();
            loadNextState = true;
            logger.info("Starting MainMenuState.", this, __LINE__);
            states.push(std::make_unique<MainMenuState>(window, states, supportedKeys, assetManager, soundManager));
        }
        logger.info("Ending state.", this, __LINE__);
        endState();
    }
}

void LoadingGameState::render(std::shared_ptr<sf::RenderWindow> window) {
    if (allAssetsLoaded) {
        window->draw(backGround);
        window->draw(progressBar);
        window->draw(typeOfAssetsBeingLoaded);
        window->draw(assetBeingLoaded);
    }
}

void LoadingGameState::loadAsset(Asset& asset) {
    window->clear(backGroundColor);
    typeOfAssetsBeingLoaded.setString("Loading: " + asset.name + " assets...");
    window->draw(typeOfAssetsBeingLoaded);

    int assetsLoaded{0};

    std::ifstream assetConfigFile{asset.filePath};

    if (!assetConfigFile.is_open()) {
        logger.error("Failed to open " + asset.name + " assets config file.", this, __LINE__);
        std::exit(-1);
    }

    if (utilities::isFileEmpty(assetConfigFile)) {
        logger.warning(asset.name + " assets config file empty. Skipping...", this, __LINE__);
        assetBeingLoaded.setString("Loading: " + asset.name + " assets config file empty. Skipping...");
        window->draw(assetBeingLoaded);
        window->display();
        asset.loaded = true; // Stops an infinite loop from happening.
//        delayForMilliseconds(5000);

    } else {
        // Color Assets
        if (asset.name == COLOR_ASSETS_NAME) {
            std::string name;
            int r, g, b, a;

            try {
                while (assetConfigFile >> name >> r >> g >> b >> a) {
                    assetManager.loadColor(name, sf::Color{static_cast<sf::Uint8>(r), static_cast<sf::Uint8>(g),
                                                           static_cast<sf::Uint8>(b), static_cast<sf::Uint8>(a)});
                    assetsLoaded++;

                    logger.debug("Loading Color: " + name + " => rgba(" + std::to_string(r) + ", " + std::to_string(g) +
                                 ", " + std::to_string(b) + ", " + std::to_string(a) + "). (" +
                                 std::to_string(assetsLoaded) + "/" + std::to_string(asset.numberOfAssets) + ").",
                                 this, __LINE__);

                    window->clear(backGroundColor);
                    assetBeingLoaded.setString(
                            "Loading Color: " + name + " => rgba(" + std::to_string(r) + ", " + std::to_string(g) +
                            ", " + std::to_string(b) + ", " + std::to_string(a) + ")");
                    window->draw(assetBeingLoaded);
                    window->draw(typeOfAssetsBeingLoaded);

                    calculateProgress(assetsLoaded, asset.numberOfAssets);
                    progressBar.setSize(sf::Vector2f(PROGRESS_BAR_LENGTH * progress, PROGRESS_BAR_HEIGHT));
                    window->draw(progressBar);
                    window->display();
//                delayForMilliseconds(300);
                }
            } catch (const std::exception& ex) {
                std::string exception{ex.what()};
                logger.error("Exception caught: " + exception, this, __LINE__);
            }
        }
        // Font, Texture & Sound Assets
        else {
            std::string name;
            std::string path;

            try {
                while (assetConfigFile >> name >> path) {
                    if (asset.name == FONT_ASSETS_NAME) {
                        assetManager.loadFont(name, path);
                    } else if (asset.name == TEXTURE_ASSETS_NAME) {
                        assetManager.loadTexture(name, path);
                    } else if (asset.name == SOUND_ASSETS_NAME) {
                        assetManager.loadSound(name, path);
                    }

                    assetsLoaded++;
                    logger.debug("Loading " + asset.name + ": " + name + " => '" + path + "' (" +
                                 std::to_string(assetsLoaded) + "/" +
                                 std::to_string((asset.numberOfAssets == 0) ? 1 : asset.numberOfAssets) + ").", this, __LINE__);

                    window->clear(backGroundColor);
                    assetBeingLoaded.setString("Loading " + asset.name + ": " + name + " => '" + path + "'");
                    window->draw(typeOfAssetsBeingLoaded);
                    window->draw(assetBeingLoaded);

                    calculateProgress(assetsLoaded, (asset.numberOfAssets == 0) ? 1 : asset.numberOfAssets);
                    progressBar.setSize(sf::Vector2f(PROGRESS_BAR_LENGTH * progress, PROGRESS_BAR_HEIGHT));
                    window->draw(progressBar);
                    window->display();
//                delayForMilliseconds(300);
                }
            } catch (std::exception& ex) {
                std::string exception{ex.what()};
                logger.error("Exception caught: " + exception, this, __LINE__);
            }
        }
        asset.loaded = true;
        progress = 0.f;
        logger.info("Successfully loaded " + asset.name + " assets.", this, __LINE__);

        window->clear(sf::Color{43, 43, 43, 255});
        typeOfAssetsBeingLoaded.setString("Successfully loaded " + asset.name + " assets");
        assetBeingLoaded.setString("Waiting...");
        progressBar.setSize(sf::Vector2f(0.f, 0.f));
        window->draw(progressBar);
        window->draw(typeOfAssetsBeingLoaded);
        window->draw(assetBeingLoaded);
        window->display();
//        delayForMilliseconds(500);
    }
    assetConfigFile.close();
}

bool LoadingGameState::checkIfAllAssetsLoaded() {
    return std::any_of(std::begin(assets), std::end(assets), [](const Asset& asset) {
        return asset.loaded;
    });
}

void LoadingGameState::setAllAssetsLoaded() {
    progressBar.setSize(sf::Vector2f(PROGRESS_BAR_LENGTH, PROGRESS_BAR_HEIGHT));
    typeOfAssetsBeingLoaded.setString("All assets loaded successfully.");
    assetBeingLoaded.setString("Finished.");
    window->clear(backGroundColor);
    window->draw(progressBar);
    window->draw(typeOfAssetsBeingLoaded);
    window->draw(assetBeingLoaded);
    window->display();
    delayForMilliseconds(500);

    allAssetsLoaded = true;
}

void LoadingGameState::calculateProgress(int numberOfAssetsLoaded, int totalAssetsToLoad) {
    progress = (float)numberOfAssetsLoaded / (float)totalAssetsToLoad;
}

int LoadingGameState::countLinesInAssetFiles(const char* filePath) {
    std::ifstream file(filePath);

    file.unsetf(std::ios_base::skipws);

    int lineCount = (int)std::count(std::istream_iterator<char>(file), std::istream_iterator<char>(), '\n');
    return lineCount;
}

void LoadingGameState::initBackground() {
    backGround.setSize(sf::Vector2f{static_cast<float>(window->getSize().x), static_cast<float>(window->getSize().y)});
    backGround.setFillColor(backGroundColor);
}

void LoadingGameState::initFont() {
    if (!font.loadFromFile("../assets/fonts/Pixellari.ttf")) {
        logger.error("Failed to load starting font.", this, __LINE__);
        std::exit(-1);
    }
    logger.info("Starting font loaded.", this, __LINE__);
}

void LoadingGameState::initText() {
    typeOfAssetsBeingLoaded.setFillColor(sf::Color::White);
    typeOfAssetsBeingLoaded.setPosition(200, 550);
    typeOfAssetsBeingLoaded.setCharacterSize(AssetManager::FONT_HEADING_3);
    typeOfAssetsBeingLoaded.setFont(font);
    typeOfAssetsBeingLoaded.setString("Loading: Font Assets...");

    assetBeingLoaded.setFillColor(sf::Color::White);
    assetBeingLoaded.setPosition(200, 700);
    assetBeingLoaded.setCharacterSize(AssetManager::FONT_PARAGRAPH);
    assetBeingLoaded.setFont(font);
    assetBeingLoaded.setString("Loading: ");
}

void LoadingGameState::initProgressBar() {
    progressBar.setPosition(sf::Vector2f{200, static_cast<float>(window->getSize().y)/2});
    progressBar.setOutlineColor(sf::Color::Black);
    progressBar.setOutlineThickness(5);
    progressBar.setFillColor(sf::Color::Green);
}

void LoadingGameState::initAssets() {
    Asset fonts{FONT_ASSETS_NAME, FONT_ASSETS_CONFIG, countLinesInAssetFiles(FONT_ASSETS_CONFIG)};
    Asset textures{TEXTURE_ASSETS_NAME, TEXTURE_ASSETS_CONFIG, countLinesInAssetFiles(TEXTURE_ASSETS_CONFIG)};
    Asset sounds{SOUND_ASSETS_NAME, SOUND_ASSETS_CONFIG, countLinesInAssetFiles(SOUND_ASSETS_CONFIG)};
    Asset colors{COLOR_ASSETS_NAME, COLOR_ASSETS_CONFIG, countLinesInAssetFiles(COLOR_ASSETS_CONFIG)};

    assets[0] = fonts;
    assets[1] = textures;
    assets[2] = sounds;
    assets[3] = colors;
}

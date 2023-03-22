//
// Created by Liam Ross on 21/03/2023.
//

#ifndef SPACE_INVADERS_APPLICATION_H
#define SPACE_INVADERS_APPLICATION_H

#include <Logger.h>

#include "states/MainMenuState.h"
#include "../utilities/FixedClock.h"
#include "../utilities/Utils.h"

class Application {
private:
    static constexpr const int WINDOW_HEIGHT{1500};
    static constexpr const int WINDOW_WIDTH{1500};

    static constexpr const char* SUPPORTED_KEYS_CONFIG{"../config/supportedKeys.ini"};
    static constexpr const char* FONT_ASSETS_CONFIG{"../config/fontAssets.ini"};
    static constexpr const char* TEXTURE_ASSETS_CONFIG{"../config/textureAssets.ini"};
    static constexpr const char* SOUND_ASSETS_CONFIG{"../config/soundAssets.ini"};
    static constexpr const char* COLOR_ASSETS_CONFIG{"../config/colorAssets.ini"};


    std::shared_ptr<sf::RenderWindow> window;
    sf::Event event;

    std::stack<std::unique_ptr<State>> states;
    std::map<std::string, int> supportedKeys;
    AssetManager assetManager;

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

    void initAssets();
    void initFontAssets();
    void initTextureAssets();
    void initSoundAssets();
    void initColorAssets();
};


#endif //SPACE_INVADERS_APPLICATION_H

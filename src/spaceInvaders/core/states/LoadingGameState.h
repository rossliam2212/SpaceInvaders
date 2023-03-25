//
// Created by Liam Ross on 23/03/2023.
//

#ifndef SPACE_INVADERS_LOADINGGAMESTATE_H
#define SPACE_INVADERS_LOADINGGAMESTATE_H

#include "MainMenuState.h"

struct Asset {
    std::string name;
    std::string filePath;
    int numberOfAssets;
    bool loaded{false};

    Asset() = default;
    Asset(const char* name, const char* filePath, int numberOfAssets)
        : name{name},
          filePath{filePath},
          numberOfAssets{numberOfAssets} {
    }
};

class LoadingGameState : public State {
private:
    static constexpr const char* FONT_ASSETS_NAME{"Font"};
    static constexpr const char* TEXTURE_ASSETS_NAME{"Texture"};
    static constexpr const char* SOUND_ASSETS_NAME{"Sound"};
    static constexpr const char* COLOR_ASSETS_NAME{"Color"};

    static constexpr const char* FONT_ASSETS_CONFIG{"../config/fontAssets.ini"};
    static constexpr const char* TEXTURE_ASSETS_CONFIG{"../config/textureAssets.ini"};
    static constexpr const char* SOUND_ASSETS_CONFIG{"../config/soundAssets.ini"};
    static constexpr const char* COLOR_ASSETS_CONFIG{"../config/colorAssets.ini"};

    static constexpr const int PROGRESS_BAR_LENGTH{1100};
    static constexpr const int PROGRESS_BAR_HEIGHT{75};

    sf::RectangleShape backGround;
    sf::Sprite logo;
    sf::Texture logoTexture;
    sf::Text assetBeingLoaded;
    sf::Text typeOfAssetsBeingLoaded;
    sf::Color backGroundColor;

    sf::Font font;
    sf::RectangleShape progressBar;
    float progress;

    std::array<Asset, 4> assets;

    bool loadNextState{false};
    bool allAssetsLoaded{false};

public:
    LoadingGameState(const std::shared_ptr<sf::RenderWindow>& window, std::stack<std::unique_ptr<State>>& states,
                     const std::unordered_map<std::string, int>& supportedKeys, const AssetManager& assetManager,
                     const SoundManager& soundManager) noexcept;
    ~LoadingGameState() override = default;

    void update(const float& dt) override;
    void render(std::shared_ptr<sf::RenderWindow> window) override;

private:
    void initBackground();
    void initFont();
    void initText();
    void initProgressBar();
    void initAssets();

    void setAllAssetsLoaded();

    void loadAsset(Asset& asset);
    void calculateProgress(int numberOfAssetsLoaded, int totalAssetsToLoad);
    static int countLinesInAssetFiles(const char* filePath);
    bool checkIfAllAssetsLoaded();
};


#endif //SPACE_INVADERS_LOADINGGAMESTATE_H

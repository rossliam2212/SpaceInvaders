//
// Created by Liam Ross on 21/03/2023.
//

#ifndef SPACE_INVADERS_ASSETMANAGER_H
#define SPACE_INVADERS_ASSETMANAGER_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <unordered_map>
#include <string>
#include <Logger.h>

class AssetManager {
public:
    static constexpr const int FONT_SMALL{20};
    static constexpr const int FONT_PARAGRAPH{35};
    static constexpr const int FONT_HEADING{90};
    static constexpr const int FONT_HEADING_2{70};
    static constexpr const int FONT_HEADING_3{50};

    static constexpr const int SPRITE_SCALE_UP_FACTOR{10};


private:
    std::unordered_map<std::string, sf::Texture> textures;
    std::unordered_map<std::string, sf::Font> fonts;
    std::unordered_map<std::string, sf::SoundBuffer> sounds;
    std::unordered_map<std::string, sf::Color> colors;

    logger::Logger logger;

public:
    AssetManager() noexcept;
    ~AssetManager() = default;

    void loadTexture(const std::string& name, const std::string& filename);
    sf::Texture& getTexture(const std::string& name);

    void loadFont(const std::string& name, const std::string& filename);
    sf::Font& getFont(const std::string& name);

    void loadSound(const std::string& name, const std::string& filename);
    sf::SoundBuffer& getSound(const std::string& name);

    void loadColor(const std::string& name, sf::Color color);
    sf::Color& getColor(const std::string& name);

private:
    bool isFontLoaded(const std::string& name);
    bool isTextureLoaded(const std::string& name);
    bool isSoundLoaded(const std::string& name);
    bool isColorLoaded(const std::string& name);
};


#endif //SPACE_INVADERS_ASSETMANAGER_H

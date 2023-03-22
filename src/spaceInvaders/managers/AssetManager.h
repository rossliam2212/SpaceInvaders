//
// Created by Liam Ross on 21/03/2023.
//

#ifndef SPACE_INVADERS_ASSETMANAGER_H
#define SPACE_INVADERS_ASSETMANAGER_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <unordered_map>
#include <string>

class AssetManager {
private:
    std::unordered_map<std::string, sf::Texture> textures;
    std::unordered_map<std::string, sf::Font> fonts;
    std::unordered_map<std::string, sf::SoundBuffer> sounds;
    std::unordered_map<std::string, sf::Color> colors;

public:
    AssetManager() noexcept = default;
    ~AssetManager() = default;

    void loadTexture(const std::string& name, const std::string& filename);
    sf::Texture& getTexture(const std::string& name);

    void loadFont(const std::string& name, const std::string& filename);
    sf::Font& getFont(const std::string& name);

    void loadSound(const std::string& name, const std::string& filename);
    sf::SoundBuffer& getSound(const std::string& name);

    void loadColor(const std::string& name, sf::Color color);
    sf::Color& getColor(const std::string& name);
};


#endif //SPACE_INVADERS_ASSETMANAGER_H

//
// Created by Liam Ross on 21/03/2023.
//

#include "AssetManager.h"

void AssetManager::loadTexture(const std::string& name, const std::string& filename) {
    textures[name].loadFromFile(filename);
}

sf::Texture& AssetManager::getTexture(const std::string& name) {
    return textures.at(name);
}

void AssetManager::loadFont(const std::string& name, const std::string& filename) {
    fonts[name].loadFromFile(filename);
}

sf::Font& AssetManager::getFont(const std::string& name) {
    return fonts.at(name);
}

void AssetManager::loadSound(const std::string& name, const std::string& filename) {
    sounds[name].loadFromFile(filename);
}

sf::SoundBuffer& AssetManager::getSound(const std::string& name) {
    return sounds.at(name);
}

void AssetManager::loadColor(const std::string& name, sf::Color color) {
    colors[name] = color;
}

sf::Color& AssetManager::getColor(const std::string& name) {
    return colors.at(name);
}
//
// Created by Liam Ross on 21/03/2023.
//

#include "AssetManager.h"

void AssetManager::loadTexture(const std::string& name, const std::string& filename) {
    sf::Texture texture;
    texture.loadFromFile(filename);
    textures[name] = texture;
}

sf::Texture& AssetManager::getTexture(const std::string& name) {
    return textures.at(name);
}

void AssetManager::loadFont(const std::string& name, const std::string& filename) {
    sf::Font font;
    font.loadFromFile(filename);
    fonts[name] = font;
}

sf::Font& AssetManager::getFont(const std::string& name) {
    return fonts.at(name);
}

void AssetManager::loadSound(const std::string& name, const std::string& filename) {
    sf::SoundBuffer sound;
    sound.loadFromFile(filename);
    sounds[name] = sound;
}

sf::SoundBuffer& AssetManager::getSound(const std::string& name) {
    return sounds.at(name);
}
//
// Created by Liam Ross on 21/03/2023.
//

#include "AssetManager.h"

AssetManager::AssetManager() noexcept
    : logger{"logs"} {
}

void AssetManager::loadTexture(const std::string& name, const std::string& filename) {
    if (!isTextureLoaded(name)) {
        textures[name].loadFromFile(filename);
    } else {
        logger.warning("'" + name + "' texture already loaded.", this, __LINE__);
    }
}

sf::Texture& AssetManager::getTexture(const std::string& name) {
    if (isTextureLoaded(name)) {
        return textures.at(name);
    }
    return textures.begin()->second;
}

void AssetManager::loadFont(const std::string& name, const std::string& filename) {
    if (!isFontLoaded(name)) {
        fonts[name].loadFromFile(filename);
    } else {
        logger.warning("'" + name + "' font already loaded.", this, __LINE__);
    }
}

sf::Font& AssetManager::getFont(const std::string& name) {
    if (isFontLoaded(name)) {
        return fonts.at(name);
    }
    return fonts.begin()->second;
}

void AssetManager::loadSound(const std::string& name, const std::string& filename) {
    if (!isSoundLoaded(name)) {
        sounds[name].loadFromFile(filename);
    } else {
        logger.warning("'" + name + "' sound already loaded.", this, __LINE__);
    }
}

sf::SoundBuffer& AssetManager::getSound(const std::string& name) {
    if (isSoundLoaded(name)) {
        return sounds.at(name);
    }
    return sounds.begin()->second;
}

void AssetManager::loadColor(const std::string& name, sf::Color color) {
    if (!isColorLoaded(name)) {
        colors[name] = color;
    } else {
        logger.warning("'" + name + "' color already loaded.", this, __LINE__);
    }
}

sf::Color& AssetManager::getColor(const std::string& name) {
    if (isColorLoaded(name)) {
        return colors.at(name);
    }
    return colors.begin()->second;
}

bool AssetManager::isFontLoaded(const std::string& name) {
    if (fonts.find(name) == std::end(fonts)) {
        return false;
    }
    return true;
}

bool AssetManager::isTextureLoaded(const std::string& name) {
    return textures.find(name) != std::end(textures);
}

bool AssetManager::isSoundLoaded(const std::string& name) {
    return sounds.find(name) != std::end(sounds);
}

bool AssetManager::isColorLoaded(const std::string& name) {
    return colors.find(name) != std::end(colors);
}
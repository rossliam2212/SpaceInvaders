//
// Created by Liam Ross on 22/03/2023.
//

#ifndef SPACE_INVADERS_SOUNDMANAGER_H
#define SPACE_INVADERS_SOUNDMANAGER_H

#include <SFML/Audio.hpp>
#include <string>
#include <unordered_map>

class SoundManager {
private:
    std::unordered_map<std::string, sf::Sound> soundsPLaying;

public:
    SoundManager() noexcept;
    ~SoundManager() = default;

    void startSound(const std::string& name, const sf::SoundBuffer& soundBuffer);
    void playSound(const std::string& name);
    void pauseSound(const std::string& name);
    void stopSound(const std::string& name);
};


#endif //SPACE_INVADERS_SOUNDMANAGER_H

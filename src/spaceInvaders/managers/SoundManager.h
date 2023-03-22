//
// Created by Liam Ross on 22/03/2023.
//

#ifndef SPACE_INVADERS_SOUNDMANAGER_H
#define SPACE_INVADERS_SOUNDMANAGER_H

#include <SFML/Audio.hpp>
#include <string>
#include <unordered_map>
#include <Logger.h>

class SoundManager {
private:
    std::unordered_map<std::string, sf::Sound> soundsPLaying;
    logger::Logger logger;

public:
    SoundManager() noexcept;
    ~SoundManager() = default;

    void startSound(const std::string& name, const sf::SoundBuffer& soundBuffer);

    void playSound(const std::string& name);
    void pauseSound(const std::string& name);
    void stopSound(const std::string& name);

    bool isSoundPlaying(const std::string& name);

    void setSoundToLoop(const std::string& name);
    void stopSoundLoop(const std::string& name);

    void setSoundVolume(const std::string& name, float volume);
    float getVolume(const std::string& name);

private:
    bool checkSound(const std::string& name);
};


#endif //SPACE_INVADERS_SOUNDMANAGER_H

//
// Created by Liam Ross on 22/03/2023.
//

#include "SoundManager.h"

void SoundManager::startSound(const std::string& name, const sf::SoundBuffer& soundBuffer) {
    sf::Sound sound;
    sound.setBuffer(soundBuffer);
    soundsPLaying[name] = sound;
    soundsPLaying.at(name).play();
}

void SoundManager::playSound(const std::string& name) {
    // TODO Add check to see if the song is already playing and in the map
    soundsPLaying.at(name).play();
}

void SoundManager::pauseSound(const std::string& name) {
    // TODO Add check to see if the song is already paused and in the map
    soundsPLaying.at(name).pause();
}

void SoundManager::stopSound(const std::string& name) {
    // TODO Remove sound form soundsPlaying map when stop is called.
    soundsPLaying.at(name).stop();
}

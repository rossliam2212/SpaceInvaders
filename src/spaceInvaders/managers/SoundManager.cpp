//
// Created by Liam Ross on 22/03/2023.
//

#include "SoundManager.h"

SoundManager::SoundManager() noexcept
    : logger{"logs"} {
}

void SoundManager::startSound(const std::string& name, const sf::SoundBuffer& soundBuffer) {
    sf::Sound sound;
    sound.setBuffer(soundBuffer);
    soundsPLaying[name] = sound;
    soundsPLaying.at(name).play();
}

void SoundManager::playSound(const std::string& name) {
    if (!checkSound(name)) {
        logger.warning("'" + name + "' sound not currently playing.", this);
    } else {
        if (soundsPLaying.at(name).getStatus() == sf::SoundSource::Paused) {
            logger.info("'" + name + "' sound => Playing.", this);
            soundsPLaying.at(name).play();
        } else {
            logger.warning("'" + name + "' sound already playing.", this);
        }
    }
}

void SoundManager::pauseSound(const std::string& name) {
    if (!checkSound(name)) {
        logger.warning("'" + name + "' sound not currently playing.", this);
    } else {
        if (soundsPLaying.at(name).getStatus() == sf::SoundSource::Playing) {
            logger.info("'" + name + "' sound => Paused.", this);
            soundsPLaying.at(name).pause();
        } else {
            logger.warning("'" + name + "' sound already paused.", this);
        }
    }
}

void SoundManager::stopSound(const std::string& name) {
    if (!checkSound(name)) {
        logger.warning("'" + name + "' sound not currently playing.", this);
    } else {
        logger.info("'" + name + "' sound => Stopped.", this);

        auto iter{soundsPLaying.find(name)};
        soundsPLaying.erase(iter);
    }
}

bool SoundManager::isSoundPlaying(const std::string& name) {
    return soundsPLaying.find(name) != std::end(soundsPLaying) &&
           soundsPLaying.at(name).getStatus() != sf::SoundSource::Paused;
}

void SoundManager::setSoundToLoop(const std::string& name) {
    if (!checkSound(name)) {
        logger.warning("'" + name + "' sound not currently playing.", this);
    } else {
        soundsPLaying.at(name).setLoop(true);
    }
}

void SoundManager::stopSoundLoop(const std::string& name) {
    if (!checkSound(name)) {
        logger.warning("'" + name + "' sound not currently playing.", this);
    } else {
        soundsPLaying.at(name).setLoop(false);
    }
}

void SoundManager::setSoundVolume(const std::string& name, float volume) {
    if (!checkSound(name)) {
        logger.warning("'" + name + "' sound not currently playing.", this);
    } else if (volume > 100 || volume < 0) {
        logger.error("Value for sound volume must be between 0 and 100.", this);
    } else {
        soundsPLaying.at(name).setVolume(volume);
    }
}

float SoundManager::getVolume(const std::string& name) {
    if (!checkSound(name)) {
        logger.warning("'" + name + "' sound not currently playing.", this);
        return 0.f;
    } else {
        return soundsPLaying.at(name).getVolume();
    }
}


bool SoundManager::checkSound(const std::string& name) {
    if (soundsPLaying.find(name) == std::end(soundsPLaying)) {
        logger.warning("'" + name + "' sound not currently playing.", this);
        return false;
    }
    return true;
}

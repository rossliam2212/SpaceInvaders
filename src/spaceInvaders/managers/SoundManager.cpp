//
// Created by Liam Ross on 22/03/2023.
//

#include "SoundManager.h"

SoundManager::SoundManager() noexcept
    : logger{"logs"} {
}

/**
 * Starts playing a sound.
 * @param name The name of the sound.
 * @param soundBuffer The sound buffer.
 */
void SoundManager::startSound(const std::string& name, const sf::SoundBuffer& soundBuffer) {
    sf::Sound sound;
    sound.setBuffer(soundBuffer);
    soundsPLaying[name] = sound;
    soundsPLaying.at(name).play();
}

/**
 * Plays a sound after the sound has been paused.
 * @param name The name of the sound to play.
 */
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

/**
 * Pauses a sound that is currently playing.
 * @param name The name of the sound to pause.
 */
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

/**
 * Stops a sound from playing.
 * @param name The name of the sound to pause.
 */
void SoundManager::stopSound(const std::string& name) {
    if (!checkSound(name)) {
        logger.warning("'" + name + "' sound not currently playing.", this);
    } else {
        logger.info("'" + name + "' sound => Stopped.", this);

        auto iter{soundsPLaying.find(name)};
        soundsPLaying.erase(iter);
    }
}

/**
 * Checks if a a sound is currently playing.
 * @param name The name of the sound to check.
 * @return True if the sound is playing, False otherwise.
 */
bool SoundManager::isSoundPlaying(const std::string& name) {
    return soundsPLaying.find(name) != std::end(soundsPLaying) &&
           soundsPLaying.at(name).getStatus() != sf::SoundSource::Paused;
}

/**
 * Sets a sound to loop.
 * @param name The name of the sound to set to loop.
 */
void SoundManager::setSoundToLoop(const std::string& name) {
    if (!checkSound(name)) {
        logger.warning("'" + name + "' sound not currently playing.", this);
    } else {
        soundsPLaying.at(name).setLoop(true);
    }
}

/**
 * Sets a sound to stop looping.
 * @param name The name of the sound to set to not loop.
 */
void SoundManager::stopSoundLoop(const std::string& name) {
    if (!checkSound(name)) {
        logger.warning("'" + name + "' sound not currently playing.", this);
    } else {
        soundsPLaying.at(name).setLoop(false);
    }
}

/**
 * Sets the volume of a sound.
 * @param name The name of the sound to set the volume of.
 * @param volume The volume to set the sound to. (
 */
void SoundManager::setSoundVolume(const std::string& name, float volume) {
    if (!checkSound(name)) {
        logger.warning("'" + name + "' sound not currently playing.", this);
        return;
    }

    if (volume <= MAX_SOUND_VOLUME && volume >= MIN_SOUND_VOLUME) {
        soundsPLaying.at(name).setVolume(volume);
    } else {
        logger.error("Value for sound volume must be between 0 and 100.", this);
    }
}

/**
 * Gets the volume of a sound.
 * @param name The name of the sound to get the volume of.
 * @return The volume of the sound.
 */
float SoundManager::getVolume(const std::string& name) {
    if (!checkSound(name)) {
        logger.warning("'" + name + "' sound not currently playing.", this);
        return MIN_SOUND_VOLUME;
    } else {
        return soundsPLaying.at(name).getVolume();
    }
}

/**
 * Checks if the sound is in the soundsPlaying map.
 * @param name The name of the sound to check.
 * @return True if the sound is in the soundsPlaying map, False otherwise.
 */
bool SoundManager::checkSound(const std::string& name) {
    if (soundsPLaying.find(name) == std::end(soundsPLaying)) {
        logger.warning("'" + name + "' sound not currently playing.", this);
        return false;
    }
    return true;
}

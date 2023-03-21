//
// Created by Liam Ross on 21/03/2023.
//

#include "FixedClock.h"


FixedClock::FixedClock(bool startClock)
    : clock{},
      stoppedTime{sf::Time::Zero},
      running{false} {
    if (startClock)
        start();
}

void FixedClock::start() {
    if (!running) {
        running = true;
        clock.restart();
    }
}

void FixedClock::stop() {
    if (running) {
        running = false;
        stoppedTime = clock.getElapsedTime();
    }
}

void FixedClock::restart() {
    stoppedTime = sf::Time::Zero;
    running = false;
    start();
}

sf::Time FixedClock::GetElapsedTime() const {
    if (running)
        return stoppedTime + clock.getElapsedTime();

    return stoppedTime;
}

//
// Created by Liam Ross on 21/03/2023.
//

#ifndef SPACE_INVADERS_FIXEDCLOCK_H
#define SPACE_INVADERS_FIXEDCLOCK_H

#include <SFML/Graphics.hpp>

class FixedClock {
private:
    sf::Clock clock;
    sf::Time stoppedTime;
    bool running;

public:
    FixedClock(bool startClock);
    ~FixedClock() = default;

    void start();
    void stop();
    void restart();

    sf::Time GetElapsedTime() const;
};


#endif //SPACE_INVADERS_FIXEDCLOCK_H

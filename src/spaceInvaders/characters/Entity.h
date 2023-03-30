//
// Created by Liam Ross on 24/03/2023.
//

#ifndef SPACE_INVADERS_ENTITY_H
#define SPACE_INVADERS_ENTITY_H

#include <SFML/Graphics.hpp>
#include <Logger.h>
#include <string>

class Entity {
private:
    static constexpr const char* DEFAULT_NAME{"Default"};
    static constexpr const float DEFAULT_POSITION_X{0.f};
    static constexpr const float DEFAULT_POSITION_Y{0.f};

protected:
    std::string name;
    sf::Vector2f position;

    logger::Logger logger;

public:
    Entity() noexcept;
    Entity(const std::string& name, const sf::Vector2f& position) noexcept;
    virtual ~Entity() = default;

    std::string getName() const;
    sf::Vector2f getPosition() const;
    void setPosition(const sf::Vector2f& newPosition);
};


#endif //SPACE_INVADERS_ENTITY_H

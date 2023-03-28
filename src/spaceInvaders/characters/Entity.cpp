//
// Created by Liam Ross on 24/03/2023.
//

#include "Entity.h"

Entity::Entity() noexcept
    : name{DEFAULT_NAME},
      position{DEFAULT_POSITION_X, DEFAULT_POSITION_Y},
      logger{"logs"} {
}

Entity::Entity(const std::string& name, const sf::Vector2f& position) noexcept
    : name{name},
      position{position} {
}

std::string Entity::getName() const {
    return name;
}

sf::Vector2f Entity::getPosition() const {
    return position;
}

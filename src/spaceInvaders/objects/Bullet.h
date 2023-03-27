//
// Created by Liam Ross on 27/03/2023.
//

#ifndef SPACE_INVADERS_BULLET_H
#define SPACE_INVADERS_BULLET_H

#include <SFML/Graphics.hpp>
#include <memory>

class Bullet {
private:
    sf::Sprite sprite;

    int damage;
    float lifeTime;
    float timeAlive;

public:
    Bullet();
    virtual ~Bullet() = default;

    void update(const float& dt);
    void render(std::shared_ptr<sf::RenderWindow> window);

    int getDamage() const;
    bool isAlive() const;
};


#endif //SPACE_INVADERS_BULLET_H

//
// Created by Liam Ross on 23/03/2023.
//

#ifndef SPACE_INVADERS_BUTTON_H
#define SPACE_INVADERS_BUTTON_H

#include <SFML/Graphics.hpp>
#include <string>
#include <memory>

#include "../input/Input.h"

enum ButtonState {
    idle = 0,
    hover,
    active
};

class Button {
private:
    ButtonState state;

    sf::RectangleShape shape;
    sf::Font font;
    sf::Text text;

    // TODO Add idle, hover and active colors for the button text
    sf::Color idleColor;
    sf::Color hoverColor;
    sf::Color activeColor;

    bool showBG;
    bool display;

public:
    Button(float x, float y, float width, float height, const sf::Font& font, int fontSize,
           const std::string& text, sf::Color idleColor, sf::Color hoverColor,
           sf::Color activeColor, bool showBG) noexcept;
    Button(const sf::Vector2f& position, const sf::Vector2f& size, const sf::Font& font, int fontSize,
           const std::string& text, sf::Color idleColor, sf::Color hoverColor,
           sf::Color activeColor, bool showBG) noexcept;

    void update(const sf::Vector2f& mousePos);
    void render(std::shared_ptr<sf::RenderWindow> window);

    bool isPressed() const;
    bool getShouldDisplay() const;
    void setDisplay(bool shouldDisplay);
};



#endif //SPACE_INVADERS_BUTTON_H

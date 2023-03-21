//
// Created by Liam Ross on 21/03/2023.
//

#ifndef SPACE_INVADERS_INPUT_H
#define SPACE_INVADERS_INPUT_H

#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Mouse.hpp>
#include <map>
#include <string>
#include <iostream>

#include "../utilities/Utils.h"

namespace input {
    class Input {
    public:
        class KeyBoard {
        private:
            static std::map<std::string, int>* supportedKeys;
            static std::map<std::string, int>* keyBinds;
            static float slidingV;
            static float slidingH;

        public:
            enum Axis {
                Horizontal = 0,
                Vertical
            };

            static void init(std::map<std::string, int>* mySupportedKeys, std::map<std::string, int>* myKeyBinds);
            static float getAxis(const float& dt, Axis axis);
            static float getAxis(const float& dt, const std::string&& axis);

        private:
            static sf::Vector2f smoothInput(const float& dt, float v, float h);
            static float smoothInput(const float& dt, Axis axis, float value);
        };



        class Mouse {
        private:
            const static sf::RenderWindow* window;

        public:
            static void init(sf::RenderWindow* target);

            static bool mousePressed(sf::Mouse::Button btn);
            static sf::Vector2f getPosition();
            static sf::Vector2f getCoords();
            static sf::Vector2f getRelativePosition();
            static sf::Vector2f getRelativeCoords();

        };
    };
}


#endif //SPACE_INVADERS_INPUT_H

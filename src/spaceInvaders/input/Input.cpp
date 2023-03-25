//
// Created by Liam Ross on 21/03/2023.
//

#include "Input.h"

namespace input {
    // ***************************
    // ***** Key Board Class *****
    // ***************************

    std::unordered_map<std::string, int>* Input::KeyBoard::supportedKeys;
    std::unordered_map<std::string, int>* Input::KeyBoard::keyBinds;
    float Input::KeyBoard::slidingV;
    float Input::KeyBoard::slidingH;

    void Input::KeyBoard::init(std::unordered_map<std::string, int>* mySupportedKeys, std::unordered_map<std::string, int>* myKeyBinds) {
        supportedKeys = mySupportedKeys;
        keyBinds = myKeyBinds;
    }

    // https://stackoverflow.com/questions/56477371/how-to-replace-input-getaxis-with-a-manual-code
    float Input::KeyBoard::getAxis(const float& dt, Input::KeyBoard::Axis axis) {
        if (axis == Vertical) {
            float v{0.f};

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(keyBinds->at("MOVE_UP"))))
//            if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
                v = -1.f;
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(keyBinds->at("MOVE_DOWN"))))
//            if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
                v = 1.f;

            return smoothInput(dt, axis, v);
        }
        else {
            float h{0.f};

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(keyBinds->at("MOVE_LEFT"))))
//            if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
                h = -1.f;
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(keyBinds->at("MOVE_RIGHT"))))
//            if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
                h = 1.f;

            return smoothInput(dt, axis, h);
        }
    }

    float Input::KeyBoard::getAxis(const float& dt, const std::string&& axis) {
        if (axis == "Horizontal")
            return getAxis(dt, Horizontal);
        else if (axis == "Vertical")
            return getAxis(dt, Vertical);
        else {
            std::cerr << "[ERROR] - Invalid Axis\n";
            exit(-1);
        }
    }

    sf::Vector2f Input::KeyBoard::smoothInput(const float& dt, float v, float h) {
        const float sensitivity{5.f};
        const float deadZone = {0.001f};

        slidingV = utilities::moveTowards(slidingH, v, sensitivity*dt);
        slidingH = utilities::moveTowards(slidingH, h, sensitivity*dt);

        return sf::Vector2f{
                (abs(slidingV) < deadZone) ? 0.f : slidingV,
                (abs(slidingH) < deadZone) ? 0.f : slidingH
        };
    }

    float Input::KeyBoard::smoothInput(const float& dt, Axis axis, float value) {
        const float sensitivity{3.f};
        const float deadZone{0.0001f};

        if (axis == Vertical) {
            slidingV = utilities::moveTowards(slidingV, value, sensitivity*dt);
            return (abs(slidingV) < deadZone) ? 0.f : slidingV;
        }
        else {
            slidingH = utilities::moveTowards(slidingH, value, sensitivity*dt);
            return (abs(slidingH) < deadZone) ? 0.f : slidingH;
        }
    }

    // ***********************
    // ***** Mouse Class *****
    // ***********************
    const sf::RenderWindow* Input::Mouse::window;

    void Input::Mouse::init(sf::RenderWindow* target) {
        window = target;
    }

    bool Input::Mouse::mousePressed(sf::Mouse::Button btn) {
        return sf::Mouse::isButtonPressed(btn);
    }

    sf::Vector2f Input::Mouse::getPosition() {
        if (!window->getSystemHandle())
            return {};
        return (sf::Vector2f)sf::Mouse::getPosition();
    }

    sf::Vector2f Input::Mouse::getCoords() {
        if (!window->getSystemHandle())
            return {};
        return window->mapPixelToCoords(sf::Mouse::getPosition());
    }

    sf::Vector2f Input::Mouse::getRelativePosition() {
        if (!window->getSystemHandle())
            return {};
        return (sf::Vector2f)sf::Mouse::getPosition(*window);
    }

    sf::Vector2f Input::Mouse::getRelativeCoords() {
        if (!window->getSystemHandle())
            return {};
        return window->mapPixelToCoords(sf::Mouse::getPosition(*window));
    }
}
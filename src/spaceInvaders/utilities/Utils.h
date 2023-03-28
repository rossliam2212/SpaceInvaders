//
// Created by Liam Ross on 21/03/2023.
//

#ifndef SPACE_INVADERS_UTILS_H
#define SPACE_INVADERS_UTILS_H

#include <SFML/Graphics.hpp>
#include <cmath>
#include <fstream>
#include <random>
#include <algorithm>

namespace utilities {
        // Radians to Degrees conversion constant.
        static constexpr float Rad2Deg{57.29578f};
        // Degrees to Radians conversion constant.
        static constexpr float Deg2Rad{0.01745329f};

        double degreesToRadians(double degrees);
        double radiansToDegrees(double radians);


        float length(const sf::Vector2f& v);
        sf::Vector2f normalize(const sf::Vector2f& v);
        float magnitude(const sf::Vector2f& v);
        float distance(const sf::Vector2f& a, const sf::Vector2f& b);
        float lerp(float start, float end, float speed);
        float clamp(float value, float min, float max);
        float moveTowards(float current, float target, float delta);
        float sign(float f);

        bool checkCollision(sf::FloatRect& first, sf::FloatRect& second);

        int randomInt(int min, int max);

        template<typename T>
        T randomFloat(T min, T max) {
            std::random_device rd;
            std::mt19937 mt(rd());
            std::uniform_real_distribution<T> dist(min, max);

            return dist(mt);
        }


        bool isFileEmpty(std::ifstream& file);
    }


#endif //SPACE_INVADERS_UTILS_H

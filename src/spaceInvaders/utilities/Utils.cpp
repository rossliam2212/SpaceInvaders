//
// Created by Liam Ross on 21/03/2023.
//

#include "Utils.h"

namespace utilities {
    float length(const sf::Vector2f& v) {
        return std::sqrt((v.x * v.x) + (v.y * v.y));
    }

    sf::Vector2f normalize(const sf::Vector2f& v) {
        float l{length(v)};
        return l != 0 ? sf::Vector2f(v.x / l, v.y / l) : v;
    }

    float magnitude(const sf::Vector2f& v) {
        return std::sqrt((v.x * v.x) + (v.y) * v.y);
    }

    float distance(const sf::Vector2f& a, const sf::Vector2f& b) {
        float num1{a.x - b.x};
        float num2{a.y - b.y};
        return std::sqrt((num1 * num1) + (num2 * num2));
    }

    float lerp(float start, float end, float t) {
        return (1 - t) * start + t * end;
    }

    float clamp(float value, float min, float max) {
        return std::min(std::max(value, min), max);
    }

    float moveTowards(float current, float target, float delta) {
        if (abs(target - current) <= delta)
            return target;

        return current + sign(target - current) * delta;
    }

    float sign(float f) {
        return f >= 0 ? 1 : -1;
    }

    bool checkCollision(sf::FloatRect& first, sf::FloatRect& second) {
        return first.intersects(second);
    }


    double degreesToRadians(double degrees) {
        return (degrees * (M_PI / 180));
    }

    double radiansToDegrees(double radians) {
        return  (radians * (180 / M_PI));
    }

    int randomInt(int min, int max) {
        std::random_device rd;
        std::mt19937 mt(rd());
        std::uniform_int_distribution<int> dist(min, max);

        return dist(mt);
    }

    bool isFileEmpty(std::ifstream& file) {
        return file.peek() == std::ifstream::traits_type::eof();
    }

}
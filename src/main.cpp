#include <iostream>
#include <Logger.h>

#include <SFML/Graphics.hpp>
#include <string>

int main() {
    std::cout << "Hello, World!\n";
    std::string name{"Liam"};
    logger::Logger logger;
    logger.info("Hello" + name);
    return 0;
}

//
// Created by Liam Ross on 15/02/2023.
//

#ifndef LOGGER_TIME_H
#define LOGGER_TIME_H

#include <string>
#include <sstream>
#include <iomanip>

namespace logger {
    class Date {
    public:
        std::string getDateAndTime() const;
    };
}


#endif //LOGGER_TIME_H

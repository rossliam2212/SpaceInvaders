//
// Created by Liam Ross on 15/02/2023.
//

#ifndef LOGGER_DATE_H
#define LOGGER_DATE_H

#include <string>
#include <sstream>
#include <iomanip>

namespace logger {
    class Date {
    public:
        std::string getDateAndTime() const;
    };
}


#endif //DATE_TIME_H

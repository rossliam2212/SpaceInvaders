//
// Created by Liam Ross on 15/02/2023.
//

#include "Time.h"

namespace logger {
    std::string Time::getDateAndTime() const {
        std::ostringstream ss;
        std::time_t t =  std::time(NULL);
        ss << std::put_time(std::localtime(&t), "%d/%m/%y  %T");
        return ss.str();
    }
}
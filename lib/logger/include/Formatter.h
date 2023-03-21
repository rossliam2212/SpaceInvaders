//
// Created by Liam Ross on 10/03/2023.
//

#ifndef LOGGER_FORMATTER_H
#define LOGGER_FORMATTER_H

#include <string>
#include <sstream>

#include "Record.h"

namespace logger {
    class Record;

    class Formatter {
    private:
        static constexpr const int MAX_SEVERITY_TEXT_LENGTH{6};

    public:
        static std::string formatConsole(const Record& record);
        static std::string formatFile(const Record& record);
    };
}


#endif //LOGGER_FORMATTER_H

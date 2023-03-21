//
// Created by Liam Ross on 12/03/2023.
//

#ifndef LOGGER_COLOR_H
#define LOGGER_COLOR_H

#include <map>
#include "Record.h"

namespace logger {
    enum Severity : unsigned short;

    enum RecordColor {
        white,
        green,
        blue,
        red,
        magenta,
        yellow,
        cyan,
        redBG,
        greenBG,
        blueBG,
        magentaBG,
        yellowBG,
        cyanBG,
        reset
    };

    class Color {
    private:
        static std::map<RecordColor, std::string> colors;
        static std::map<Severity, std::string> recordColors;

    public:
        static void init();
        static void changeRecordColor(Severity severity, RecordColor color);

        static std::map<RecordColor, std::string> getColors();
        static std::map<Severity, std::string> getRecordColors();
    };
}


#endif //LOGGER_COLOR_H

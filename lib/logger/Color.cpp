//
// Created by Liam Ross on 12/03/2023.
//

#include "include/Color.h"

namespace logger {
    std::map<logger::RecordColor, std::string> Color::colors;
    std::map<logger::Severity, std::string> Color::recordColors;

    void Color::init() {
        colors[white] = "\x1B[97m";
        colors[green] = "\x1B[32m";
        colors[blue] = "\x1B[34m";
        colors[red] = "\x1B[31m";
        colors[magenta] = "\x1B[35m";
        colors[yellow] = "\x1B[93m";
        colors[cyan] = "\x1B[36m";
        colors[redBG] = "\x1B[101m";
        colors[greenBG] = "\x1B[42m";
        colors[blueBG] = "\x1B[44m";
        colors[magentaBG] = "\x1B[45m";
        colors[yellowBG] = "\x1B[43m";
        colors[cyanBG] = "\x1B[46m";
        colors[reset] = "\x1B[0m";

        recordColors[Severity::start] = colors[green];
        recordColors[Severity::end] = colors[green];
        recordColors[Severity::info] = colors[white];
        recordColors[Severity::debug] = colors[blue];
        recordColors[Severity::warning] = colors[yellow];
        recordColors[Severity::error] = colors[red];
        recordColors[Severity::fatal] = colors[redBG];
    }

    void Color::changeRecordColor(Severity severity, RecordColor color) {
        recordColors[severity] = colors[color];
    }

    std::map<RecordColor, std::string> Color::getColors() {
        return colors;
    }

    std::map<Severity, std::string> Color::getRecordColors() {
        return recordColors;
    }
}
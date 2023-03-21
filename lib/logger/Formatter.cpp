//
// Created by Liam Ross on 10/03/2023.
//

#include "include/Formatter.h"

namespace logger {
    std::string Formatter::formatConsole(const Record& record) {
        std::ostringstream ss;
        ss << Record::getColor(record.getSeverity());
        ss << record.getTime().getDateAndTime() << "  ";
        ss << std::setw(MAX_SEVERITY_TEXT_LENGTH) << std::left << Record::getSeverityText(record.getSeverity());

        if (record.getClassName().empty())
            ss << " []  " << record.getMessage();
        else
            ss << " [" << record.getClassName() << "]  " << record.getMessage();

        ss << Color::getColors()[RecordColor::white];
        ss << Color::getColors()[RecordColor::reset];

        return ss.str();
    }

    std::string Formatter::formatFile(const Record& record) {
        std::ostringstream ss;
        ss << record.getTime().getDateAndTime() << "  ";
        ss << std::setw(MAX_SEVERITY_TEXT_LENGTH) << std::left << Record::getSeverityText(record.getSeverity());

        if (record.getClassName().empty())
            ss << " []  " << record.getMessage();
        else
            ss << " [" << record.getClassName() << "]  " << record.getMessage();

        return ss.str();
    }
}
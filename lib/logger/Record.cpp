//
// Created by Liam Ross on 15/02/2023.
//

#include "include/Record.h"

namespace logger {
    Record::Record(const std::string& message, Severity severity)
        : clasName{""},
          message{message},
          severity{severity},
          d{} {
    }

    Record::Record(const std::string& message, logger::Severity severity, const std::string& className)
        :  clasName{className},
           message{message},
           severity{severity},
           d{} {
    }

    std::string Record::getSeverityText(Severity s) {
        switch (s) {
            case start:
                return "START";
            case end:
                return "END";
            case info:
                return "INFO";
            case debug:
                return "DEBUG";
            case warning:
                return "WARN";
            case error:
                return "ERROR";
            case fatal:
                return "FATAL";
        }
    }

    std::string Record::getColor(Severity s) {
        switch (s) {
            case start:
            case end:
                return Color::getRecordColors()[Severity::start];
            case info:
                return Color::getRecordColors()[Severity::info];
            case debug:
                return Color::getRecordColors()[Severity::debug];
            case warning:
                return Color::getRecordColors()[Severity::warning];
            case error:
                return Color::getRecordColors()[Severity::error];
            case fatal:
                return Color::getRecordColors()[Severity::fatal];
        }
    }

    std::string Record::getClassName() const {
        return clasName;
    }

    Date Record::getTime() const {
        return d;
    }

    std::string Record::getMessage() const {
        return message;
    }

    Severity Record::getSeverity() const {
        return severity;
    }

    std::ostream& operator<<(std::ostream& os, const Record& record) {
        os << Formatter::formatConsole(record);
        return os;
    }
}
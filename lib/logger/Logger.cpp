//
// Created by Liam Ross on 15/02/2023.
//

#include "include/Logger.h"

namespace logger {
    Logger::Logger()
        : out{"NOT-USED"},
          outputLogsToFile{false} {
        Color::init();
    }

    Logger::Logger(const std::string& outputFileName)
        : out{outputFileName},
          outputLogsToFile{true} {
        Color::init();
    }

    void Logger::start(const std::string& message) {
        log({message, logger::end});
    }

    void Logger::end(const std::string& message) {
        log({message, logger::end});
    }

    void Logger::info(const std::string& message) {
        log({message, logger::info});
    }

    void Logger::debug(const std::string& message) {
        log({message, logger::debug});
    }

    void Logger::warning(const std::string& message) {
        log({message, logger::warning});
    }

    void Logger::error(const std::string& message) {
        log({message, logger::error});
    }

    void Logger::fatal(const std::string& message) {
        log({message, logger::fatal});
    }

    void Logger::log(const Record& record) {
        if (outputLogsToFile)
            out.output(record);

        std::cout << record << "\n";
    }

    std::string Logger::getWhereLogged() const {
        if (outputLogsToFile)
            return out.getOutputFilePath();
        else
            return "Logs were NOT outputted to a file.";
    }

    void Logger::changeRecordColor(Severity severity, RecordColor color) {
        Color::changeRecordColor(severity, color);
    }
}

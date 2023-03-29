//
// Created by Liam Ross on 15/02/2023.
//

#include "Logger.h"

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
        log({message, logger::end, false, Record::NO_EXECUTION_TIME});
    }

    void Logger::end(const std::string& message) {
        log({message, logger::end, false, Record::NO_EXECUTION_TIME});
    }

    void Logger::info(const std::string& message) {
        log({message, logger::info, false, Record::NO_EXECUTION_TIME});
    }

    void Logger::debug(const std::string& message) {
        log({message, logger::debug, false, Record::NO_EXECUTION_TIME});
    }

    void Logger::warning(const std::string& message) {
        log({message, logger::warning, false, Record::NO_EXECUTION_TIME});
    }

    void Logger::error(const std::string& message) {
        log({message, logger::error, false, Record::NO_EXECUTION_TIME});
    }

    void Logger::fatal(const std::string& message) {
        log({message, logger::fatal, false, Record::NO_EXECUTION_TIME});
    }

    void Logger::timing(const std::string& functionName, long executionTime) {
        log({functionName, logger::timing, true, executionTime});
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

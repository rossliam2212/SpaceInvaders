//
// Created by Liam Ross on 15/02/2023.
//

#ifndef LOGGER_LOGGER_H
#define LOGGER_LOGGER_H

#include <iostream>
#include <typeinfo>

#include "Outputter.h"
#include "Record.h"
#include "Color.h"

namespace logger {
    class Logger {
    private:
        Outputter out;
        bool outputLogsToFile;

        std::map<Severity, std::string> colors;

    public:
        Logger();
        explicit Logger(const std::string& outputFileName);

        template<typename T>
        void start(const std::string& message, const T& type, int line) {
            std::string className{getClassName(type)};
            log({message, logger::start, className, false, Record::NO_EXECUTION_TIME, line});
        }

        template<typename T>
        void end(const std::string& message, const T& type, int line) {
            std::string className{getClassName(type)};
            log({message, logger::end, className, false, Record::NO_EXECUTION_TIME, line});
        }

        template<typename T>
        void info(const std::string& message, const T& type, int line) {
            std::string className{getClassName(type)};
            log({message, logger::info, className, false, Record::NO_EXECUTION_TIME, line});
        }

        template<typename T>
        void debug(const std::string& message, const T& type, int line) {
            std::string className{getClassName(type)};
            log({message, logger::debug, className, false, Record::NO_EXECUTION_TIME, line});
        }

        template<typename T>
        void warning(const std::string& message, const T& type, int line) {
            std::string className{getClassName(type)};
            log({message, logger::warning, className, false, Record::NO_EXECUTION_TIME, line});
        }

        template<typename T>
        void error(const std::string& message, const T& type, int line) {
            std::string className{getClassName(type)};
            log({message, logger::error, className, false, Record::NO_EXECUTION_TIME, line});
        }

        template<typename T>
        void fatal(const std::string& message, const T& type, int line) {
            std::string className{getClassName(type)};
            log({message, logger::fatal, className, false, Record::NO_EXECUTION_TIME, line});
        }

        template<typename T>
        void timing(const std::string& functionName, long executionTime, const T& type, int line) {
            std::string className{getClassName(type)};
            log({functionName, logger::timing, className, true, executionTime, line});
        }

        void start(const std::string& message);
        void end(const std::string& message);
        void info(const std::string& message);
        void debug(const std::string& message);
        void warning(const std::string& message);
        void error(const std::string& message);
        void fatal(const std::string& message);
        void timing(const std::string& functionName, long executionTime);

        static void changeRecordColor(Severity severity, RecordColor color);

        std::string getWhereLogged() const;

    private:
        void log(const Record& record);

        template<typename T>
        std::string getClassName(T type) {
            std::string tmp{typeid(type).name()};
            std::string className;

            // Removing the numbers
            for (const auto& c : tmp) {
                if (!isdigit(c)) {
                    className += c;
                }
            }
            return className.substr(1); // Removing the first letter
        }
    };
}

#endif //LOGGER_LOGGER_H

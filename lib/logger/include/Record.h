//
// Created by Liam Ross on 15/02/2023.
//

#ifndef LOGGER_RECORD_H
#define LOGGER_RECORD_H

#include <map>
#include <iomanip>

#include "Date.h"
#include "Formatter.h"
#include "Color.h"

namespace logger {
    class Formatter;

    enum Severity : unsigned short {
        start,
        end,
        info,
        debug,
        warning,
        error,
        fatal,
        timing
    };

    class Record {
        friend std::ostream& operator<<(std::ostream& os, const Record& record);

    public:
        static constexpr const long NO_EXECUTION_TIME{0};

    private:
        std::string clasName;
        Date d;
        std::string message;
        Severity severity;

        bool isTiming;
        long executionTime;

    public:
        Record(const std::string& message, Severity severity, bool timing, long executionTime);
        Record(const std::string& message, Severity severity, const std::string& className, bool timing, long executionTime);

        static std::string getSeverityText(Severity s) ;
        static std::string getColor(Severity s) ;

        std::string getClassName() const;
        Date getTime() const;
        std::string getMessage() const;
        Severity getSeverity() const;
        bool getIsTiming() const;
        long getExecutionTime() const;
    };
}


#endif //LOGGER_RECORD_H

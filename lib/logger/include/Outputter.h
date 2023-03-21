//
// Created by Liam Ross on 15/02/2023.
//

#ifndef LOGGER_OUTPUTTER_H
#define LOGGER_OUTPUTTER_H

#include <iostream>
#include <string>
#include <fstream>
#include <filesystem>
#include <sstream>

#include "Record.h"
#include "Formatter.h"

namespace logger {
    namespace fs = std::filesystem;

    class Outputter {
    public:
        static constexpr const char* OUTPUT_DIR{"../logs/"};

    private:
        std::string outputFileName;
        std::string outputFilePath;

    public:
        explicit Outputter(std::string  fileName);
        void output(const Record& record);

        std::string getOutputFileName() const;
        std::string getOutputFilePath() const;

    private:
        void init();
        static bool setUpDirectory();
        bool setUpFile();
    };
}

#endif //LOGGER_OUTPUTTER_H

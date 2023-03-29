//
// Created by Liam Ross on 15/02/2023.
//

#include "include/Outputter.h"

namespace logger {
    Outputter::Outputter(std::string  fileName)
        : outputFileName{std::move(fileName)} {
        init();
    }

    void Outputter::init() {
        if (!setUpDirectory()) {
            std::cerr << "Error setting up '" << OUTPUT_DIR << "' directory.";
            exit(-1);
        }

        if (!setUpFile()) {
            std::cerr << "Error setting up '" << outputFileName << "' file.";
            exit(-1);
        }
    }

    bool Outputter::setUpDirectory() {
        if (!fs::create_directories(OUTPUT_DIR)) {
            if (fs::exists(OUTPUT_DIR)) {
                return true;
            }
            return false;
        }
        return true;
    }

    bool Outputter::setUpFile() {
        outputFileName += ".txt";

        std::ostringstream ss;
        ss << OUTPUT_DIR << outputFileName;
        outputFilePath = ss.str();

        std::ofstream out{outputFilePath, std::ios::app};

        if (!out)
            return false;

        out.close();
        return true;
    }

    void Outputter::output(const Record& record) {
        std::ofstream out{outputFilePath, std::ios::app};
        out << Formatter::formatFile(record) << "\n";
        out.close();
    }

    std::string Outputter::getOutputFileName() const {
        return outputFileName;
    }

    std::string Outputter::getOutputFilePath() const {
        return outputFilePath;
    }
}

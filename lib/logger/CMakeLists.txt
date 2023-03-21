cmake_minimum_required(VERSION 3.23)
project(logger)

set(CMAKE_CXX_STANDARD 17)

set(LOGGER_SOURCE_FILES
        Color.cpp
        Formatter.cpp
        Logger.cpp
        Outputter.cpp
        Record.cpp
        Date.cpp)

set(LOGGER_HEADER_FILES
        include/Color.h
        include/Formatter.h
        include/Logger.h
        include/Outputter.h
        include/Record.h
        include/Date.h)

# Include the header files for the logger library
add_library(logger STATIC ${LOGGER_HEADER_FILES} ${LOGGER_SOURCE_FILES})

# Set the output directory for the logger library
set_target_properties(logger PROPERTIES ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/lib/)

target_include_directories(logger PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)



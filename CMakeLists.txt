cmake_minimum_required(VERSION 3.23)
project(space_invaders)

set(CMAKE_CXX_STANDARD 17)

add_executable(space_invaders src/main.cpp)

# SFML
find_package(SFML 2.5 COMPONENTS system window graphics network audio REQUIRED)
include_directories(/usr/local/include ${SFML_INCLUDE_DIRS})
target_link_libraries(space_invaders sfml-system sfml-window sfml-graphics sfml-audio sfml-network)

# Logger
add_subdirectory(lib/logger)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/lib/logger/include)
target_link_libraries(space_invaders logger)

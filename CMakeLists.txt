cmake_minimum_required(VERSION 3.23)
project(space_invaders)

set(CMAKE_CXX_STANDARD 17)

set(SOURCE_FILES
        src/spaceInvaders/core/states/State.cpp
        src/spaceInvaders/utilities/Utils.cpp
        src/spaceInvaders/input/Input.cpp
        src/spaceInvaders/core/Application.cpp
        src/spaceInvaders/utilities/FixedClock.cpp
        src/spaceInvaders/managers/AssetManager.cpp
        src/spaceInvaders/core/states/MainMenuState.cpp
        src/spaceInvaders/managers/SoundManager.cpp)


set(HEADER_FILES
        src/spaceInvaders/core/states/State.h
        src/spaceInvaders/utilities/Utils.h
        src/spaceInvaders/input/Input.h
        src/spaceInvaders/core/Application.cpp
        src/spaceInvaders/utilities/FixedClock.h
        src/spaceInvaders/managers/AssetManager.cpp
        src/spaceInvaders/core/states/MainMenuState.h
        src/spaceInvaders/managers/SoundManager.h)

add_executable(space_invaders src/main.cpp ${SOURCE_FILES} ${HEADER_FILES})

# SFML
find_package(SFML 2.5 COMPONENTS system window graphics network audio REQUIRED)
include_directories(/usr/local/include ${SFML_INCLUDE_DIRS})
target_link_libraries(space_invaders sfml-system sfml-window sfml-graphics sfml-audio sfml-network)

# Logger
add_subdirectory(lib/logger)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/lib/logger/include)
target_link_libraries(space_invaders logger)

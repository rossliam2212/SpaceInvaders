cmake_minimum_required(VERSION 3.23)
project(space_invaders)

set(CMAKE_CXX_STANDARD 17)

set(SOURCE_FILES
        src/spaceInvaders/core/Application.cpp
        src/spaceInvaders/core/states/State.cpp
        src/spaceInvaders/core/states/LoadingGameState.cpp
        src/spaceInvaders/core/states/MainMenuState.cpp
        src/spaceInvaders/core/states/GameState.cpp
        src/spaceInvaders/core/states/PauseState.cpp

        src/spaceInvaders/managers/AssetManager.cpp
        src/spaceInvaders/managers/SoundManager.cpp
        src/spaceInvaders/managers/EnemyManager.cpp
        src/spaceInvaders/managers/EnemyFactory.cpp
        src/spaceInvaders/managers/ObjectManager.cpp

        src/spaceInvaders/characters/Entity.cpp
        src/spaceInvaders/characters/Character.cpp
        src/spaceInvaders/characters/Player.cpp
        src/spaceInvaders/characters/Enemy.cpp
        src/spaceInvaders/characters/enemies/BlueEnemy.cpp
        src/spaceInvaders/characters/enemies/YellowEnemy.cpp
        src/spaceInvaders/characters/enemies/GreenEnemy.cpp
        src/spaceInvaders/characters/enemies/PurpleEnemy.cpp

        src/spaceInvaders/objects/Animation.cpp
        src/spaceInvaders/objects/weapons/Weapon.cpp
        src/spaceInvaders/objects/bullets/Bullet.cpp
        src/spaceInvaders/objects/bullets/PlayerBullet.cpp
        src/spaceInvaders/objects/weapons/PlayerWeapon.cpp
        src/spaceInvaders/objects/weapons/EnemyWeapon.cpp
        src/spaceInvaders/objects/bullets/EnemyBullet.cpp
        src/spaceInvaders/objects/powerUps/PowerUp.cpp
        src/spaceInvaders/objects/powerUps/ShieldPowerUp.cpp
        src/spaceInvaders/objects/powerUps/HealthPowerUp.cpp
        src/spaceInvaders/objects/Asteroid.cpp

        src/spaceInvaders/utilities/Utils.cpp
        src/spaceInvaders/utilities/FixedClock.cpp

        src/spaceInvaders/input/Input.cpp

        src/spaceInvaders/ui/Button.cpp
        src/spaceInvaders/ui/GameStateUI.cpp)


set(HEADER_FILES
        src/spaceInvaders/core/Application.h
        src/spaceInvaders/core/states/State.h
        src/spaceInvaders/core/states/LoadingGameState.h
        src/spaceInvaders/core/states/MainMenuState.h
        src/spaceInvaders/core/states/GameState.h
        src/spaceInvaders/core/states/PauseState.h

        src/spaceInvaders/managers/AssetManager.h
        src/spaceInvaders/managers/SoundManager.h
        src/spaceInvaders/managers/EnemyManager.h
        src/spaceInvaders/managers/EnemyFactory.h
        src/spaceInvaders/managers/ObjectManager.h

        src/spaceInvaders/characters/Entity.h
        src/spaceInvaders/characters/Character.h
        src/spaceInvaders/characters/Player.h
        src/spaceInvaders/characters/Enemy.h
        src/spaceInvaders/characters/enemies/BlueEnemy.h
        src/spaceInvaders/characters/enemies/YellowEnemy.h
        src/spaceInvaders/characters/enemies/GreenEnemy.h
        src/spaceInvaders/characters/enemies/PurpleEnemy.h

        src/spaceInvaders/objects/Animation.h
        src/spaceInvaders/objects/weapons/Weapon.h
        src/spaceInvaders/objects/bullets/Bullet.h
        src/spaceInvaders/objects/bullets/PlayerBullet.h
        src/spaceInvaders/objects/weapons/PlayerWeapon.h
        src/spaceInvaders/objects/weapons/EnemyWeapon.h
        src/spaceInvaders/objects/bullets/EnemyBullet.h
        src/spaceInvaders/objects/powerUps/PowerUp.h
        src/spaceInvaders/objects/powerUps/ShieldPowerUp.h
        src/spaceInvaders/objects/powerUps/HealthPowerUp.h
        src/spaceInvaders/objects/Asteroid.h

        src/spaceInvaders/utilities/Utils.h
        src/spaceInvaders/utilities/FixedClock.h

        src/spaceInvaders/input/Input.h

        src/spaceInvaders/ui/Button.h
        src/spaceInvaders/ui/GameStateUI.h)

add_executable(space_invaders src/main.cpp ${SOURCE_FILES} ${HEADER_FILES})

# SFML
find_package(SFML 2.5 COMPONENTS system window graphics network audio REQUIRED)
include_directories(/usr/local/include ${SFML_INCLUDE_DIRS})
target_link_libraries(space_invaders sfml-system sfml-window sfml-graphics sfml-audio sfml-network)

# Logger
add_subdirectory(lib/logger)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/lib/logger/include)
target_link_libraries(space_invaders logger)

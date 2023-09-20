cmake_minimum_required(VERSION 3.10)

project(retroGame VERSION 0.2)

# First for the generic no-config case (e.g. with mingw)
set( CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin )
set( CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib )
set( CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib )
# Second, for multi-config builds (e.g. msvc)
foreach( OUTPUTCONFIG ${CMAKE_CONFIGURATION_TYPES} )
    string( TOUPPER ${OUTPUTCONFIG} OUTPUTCONFIG )
    set( CMAKE_RUNTIME_OUTPUT_DIRECTORY_${OUTPUTCONFIG} ${CMAKE_BINARY_DIR}/bin )
    set( CMAKE_LIBRARY_OUTPUT_DIRECTORY_${OUTPUTCONFIG} ${CMAKE_BINARY_DIR}/lib )
    set( CMAKE_ARCHIVE_OUTPUT_DIRECTORY_${OUTPUTCONFIG} ${CMAKE_BINARY_DIR}/lib )
endforeach( OUTPUTCONFIG CMAKE_CONFIGURATION_TYPES )

set(CMAKE_CXX_STANDARD 14)

set(SFML_LOCATION "[YOUR SFML FOLDER LOCATION]")

set(CMAKE_PREFIX_PATH SFML_LOCATION)

find_package(SFML 2.6 COMPONENTS system graphics window REQUIRED)

# Specific headers that I need for each dependency

add_library(worldHeader INTERFACE)
target_include_directories(worldHeader INTERFACE "${CMAKE_SOURCE_DIR}/src/World/World.h")
# core/Game.h needed for GUI
add_library(coreGameHeader INTERFACE)
target_include_directories(coreGameHeader INTERFACE "${CMAKE_SOURCE_DIR}/src/core/Game.h")

# core/Character.h needed for monsters & player classes
add_library(coreCharacterHeader INTERFACE)
target_include_directories(coreCharacterHeader INTERFACE "${CMAKE_SOURCE_DIR}/src/core/Character.h")

# monsters/Monster.h needed for playerClasses
add_library(monsterMainHeader INTERFACE)
target_include_directories(monsterMainHeader INTERFACE "${CMAKE_SOURCE_DIR}/src/monsters/Monster.h")

# main class header
add_library(classMainHeader INTERFACE)
target_include_directories(classMainHeader INTERFACE "${CMAKE_SOURCE_DIR}/src/playerClasses/Player.h")

# Headers that Projectile uses
add_library(projectileHeaders INTERFACE)
target_include_directories(projectileHeaders INTERFACE "${CMAKE_SOURCE_DIR}/src")
target_sources(projectileHeaders INTERFACE
    "${CMAKE_SOURCE_DIR}/src/core/Character.h"
    "${CMAKE_SOURCE_DIR}/src/core/Unit.h"
    "${CMAKE_SOURCE_DIR}/src/monsters/Monster.h"
    "${CMAKE_SOURCE_DIR}/src/playerClasses/Player.h")

add_subdirectory(src/enums)
add_subdirectory(src/noise)
add_subdirectory(src/particleSystem)
add_subdirectory(src/Utilities)
add_subdirectory(src/GUI)
add_subdirectory(src/Projectile)
add_subdirectory(src/monsters)
add_subdirectory(src/playerClasses)
add_subdirectory(src/core)
add_subdirectory(src/World)

add_executable(retroGame src/main.cpp)

target_include_directories(retroGame PRIVATE "${SFML_LOCATION}/include")

target_link_libraries(retroGame PRIVATE
    sfml-graphics 
    sfml-system
    sfml-window
    enums
    utilities
    noise
    particle
    projectiles
    classes
    monster
    gui
    core
    world
    core)

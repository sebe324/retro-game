cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 17)

file(GLOB SOURCES *.cpp)
file(GLOB HEADERS *.h)

add_library(world ${SOURCES} ${HEADERS})

target_include_directories(world PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(world PUBLIC
    sfml-graphics
    sfml-window
    sfml-system
    noise
    utilities
    core)

    set_target_properties(world PROPERTIES LINKER_LANGUAGE CXX)
cmake_minimum_required(VERSION 3.0)

project(retroGame)

set(CMAKE_CXX_STANDARD 11)

find_package(SFML 2.6 COMPONENTS graphics system window REQUIRED)

add_executable(retroGame src/main.cpp)

target_link_libraries(retroGame sfml-graphics sfml-system sfml-window)
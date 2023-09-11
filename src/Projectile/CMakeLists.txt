set(CMAKE_CXX_STANDARD 17)

file(GLOB SOURCES *.cpp)

file(GLOB HEADERS *.h)

add_library(projectiles ${SOURCES} ${HEADERS})

target_include_directories(projectiles PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(projectiles PUBLIC
    sfml-graphics
    sfml-window
    sfml-system
    enums
    utilities
    particle
    projectileHeaders)

set_target_properties(projectiles PROPERTIES LINKER_LANGUAGE CXX)
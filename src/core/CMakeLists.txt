set(CMAKE_CXX_STANDARD 17)

file(GLOB SOURCES *.cpp)

file(GLOB HEADERS *.h)

add_library(core ${SOURCES} ${HEADERS})

target_include_directories(core PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}
    "/opt/homebrew/Cellar/sfml/2.6.0/include")

add_dependencies(core monster)

target_link_libraries(core PUBLIC
    sfml-graphics
    sfml-window
    sfml-system
    enums
    utilities
    noise
    particle
    gui
    projectiles
    monster
    classes
    world)

set_target_properties(core PROPERTIES LINKER_LANGUAGE CXX)
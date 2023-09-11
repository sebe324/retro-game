set(CMAKE_CXX_STANDARD 17)

file(GLOB SOURCES *.cpp)

file(GLOB HEADERS *.h)

add_library(classes ${SOURCES} ${HEADERS})

add_dependencies(classes projectiles)

target_include_directories(classes PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}
    "/opt/homebrew/Cellar/sfml/2.6.0/include")

target_link_libraries(classes PUBLIC
    sfml-graphics
    sfml-system
    sfml-window
    particle
    utilities
    coreCharacterHeader
    monster
    projectiles)

set_target_properties(classes PROPERTIES LINKER_LANGUAGE CXX)
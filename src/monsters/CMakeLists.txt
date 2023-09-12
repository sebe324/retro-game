set(CMAKE_CXX_STANDARD 17)

file(GLOB SOURCES *.cpp)

file(GLOB HEADERS *.h)

add_library(monster ${SOURCES} ${HEADERS})

add_dependencies(monster projectiles)

target_include_directories(monster PUBLIC 
    ${CMAKE_SOURCE_DIR}
    "/opt/homebrew/Cellar/sfml/2.6.0/include")

target_link_libraries(monster PUBLIC
    sfml-graphics
    sfml-system
    sfml-window
    enums
    particle
    coreCharacterHeader
    projectiles)

set_target_properties(monster PROPERTIES LINKER_LANGUAGE CXX)
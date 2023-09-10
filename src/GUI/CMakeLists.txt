set(CMAKE_CXX_STANDARD 14)

file(GLOB SOURCES *.cpp)

file(GLOB HEADERS *.h)

add_library(gui ${SOURCES} ${HEADERS})

target_include_directories(gui PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}
    "/opt/homebrew/Cellar/sfml/2.6.0/include")

target_link_libraries(gui PUBLIC
    sfml-graphics
    sfml-window
    sfml-system
    noise
    utilities
    coreGameHeader)

set_target_properties(gui PROPERTIES LINKER_LANGUAGE CXX)
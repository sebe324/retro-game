set(CMAKE_CXX_STANDARD 14)

file(GLOB SOURCES *.cpp)

file(GLOB HEADERS *.h)

add_library(particle ${SOURCES} ${HEADERS})

target_include_directories(particle PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}
    "/opt/homebrew/Cellar/sfml/2.6.0/include")

target_link_libraries(particle PUBLIC
    sfml-graphics
    sfml-system
    sfml-window)

set_target_properties(particle PROPERTIES LINKER_LANGUAGE CXX)
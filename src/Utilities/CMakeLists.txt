set(CMAKE_CXX_STANDARD 14)

file(GLOB SOURCES *.cpp)

file(GLOB HEADERS *.h)

add_library(utilities ${SOURCES} ${HEADERS})

target_include_directories(utilities PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

set_target_properties(utilities PROPERTIES LINKER_LANGUAGE CXX)
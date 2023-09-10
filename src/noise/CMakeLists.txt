set(CMAKE_CXX_STANDARD 14)

file(GLOB SOURCES *.cpp)

file(GLOB HEADERS *.h)

add_library(noise ${SOURCES} ${HEADERS})

target_include_directories(noise PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

set_target_properties(noise PROPERTIES LINKER_LANGUAGE CXX)
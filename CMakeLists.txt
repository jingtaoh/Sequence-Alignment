cmake_minimum_required(VERSION 3.8)
project(SequenceAlignment)
add_compile_options(-std=c++17)

include_directories(
        include
)

set(HEADERS
        ${CMAKE_CURRENT_SOURCE_DIR}/include/SequenceAlignment.h
        ${CMAKE_CURRENT_SOURCE_DIR}/include/utility.h
        )
set(SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/src/SequenceAlignment.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/utility.cpp)

add_executable(basic src/basic.cpp ${SOURCES})
add_executable(efficient src/efficient.cpp ${SOURCES})

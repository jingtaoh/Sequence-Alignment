cmake_minimum_required (VERSION 3.8)
project (SequenceAlignment)
add_compile_options(-std=c++14)

include_directories(
    include 
)

set(HEADERS
    ${CMAKE_CURRENT_SOURCE_DIR}/include/SequenceAlignment.h
    )
set(SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/src/SequenceAlignment.cpp
    )

add_executable(main src/main.cpp  ${SOURCES})

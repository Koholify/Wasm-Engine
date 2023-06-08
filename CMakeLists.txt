cmake_minimum_required(VERSION 3.0)

set(CMAKE_EXPORT_COMPILE_COMMANDS true)

project(KGE)

add_compile_options(-Wall -Wextra -pedantic -std=c++17)

add_subdirectory(Math)
add_subdirectory(Collections)

file(GLOB SOURCES src/*.cpp)
add_library(KGE ${SOURCES})

target_link_libraries(KGE klm)
target_link_libraries(KGE kc)

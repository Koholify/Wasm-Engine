cmake_minimum_required(VERSION 3.0)

set(CMAKE_C_COMPILER gcc)
set(CMAKE_EXPORT_COMPILE_COMMANDS true)

project(KGE LANGUAGES C)
set(CMAKE_C_STANDARD 11)

add_compile_options(-Wall -Wextra -pedantic -Werror -std=c11)

add_subdirectory(Math)
add_subdirectory(Collections)

file(GLOB SOURCES src/*.c)
add_executable(KGE ${SOURCES})

target_link_libraries(KGE klm)
target_link_libraries(KGE kc)

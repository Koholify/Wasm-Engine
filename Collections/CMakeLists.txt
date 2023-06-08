cmake_minimum_required(VERSION 3.0)

file(GLOB SOURCES_kc src/*.cpp)
add_library(kc STATIC ${SOURCES_kc})
target_include_directories(kc PUBLIC include)

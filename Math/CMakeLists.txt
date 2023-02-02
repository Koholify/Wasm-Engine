cmake_minimum_required(VERSION 3.0)

add_library(klm STATIC src/klm.c)
target_include_directories(klm PUBLIC include)

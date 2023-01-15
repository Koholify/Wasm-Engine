cmake_minimum_required(VERSION 2.8.11)

add_library(klm STATIC src/klm.c)
target_include_directories(klm PUBLIC include)

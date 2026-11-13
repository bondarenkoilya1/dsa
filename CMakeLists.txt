cmake_minimum_required(VERSION 4.2)
project(Algos C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(Algos
        enums.h
        vector.c
        vector.h
        search.c
        search.h)

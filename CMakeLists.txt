cmake_minimum_required(VERSION 3.16)
project(Progetto C)

set(CMAKE_C_STANDARD 90)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -pedantic-errors")
include_directories(.)

add_executable(Progetto
        game.c
        library.h)

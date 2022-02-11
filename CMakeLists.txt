cmake_minimum_required(VERSION 3.16)
project(xTetris)

set(CMAKE_C_STANDARD 90)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -pedantic-errors")
set(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS} -O3")

include_directories(./src)

add_executable(xTetris
        src/game.c
        src/cpu.c
        src/pieces.c
        src/players.c)

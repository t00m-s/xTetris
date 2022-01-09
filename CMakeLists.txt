cmake_minimum_required(VERSION 3.16)
project(Progetto)

set(CMAKE_C_STANDARD 90)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -pedantic-errors")
include_directories(./src)

add_executable(Progetto
        src/game.c
        src/pieces.c
        src/players.c)

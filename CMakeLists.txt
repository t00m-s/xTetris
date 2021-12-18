cmake_minimum_required(VERSION 3.16)
project(Progetto)

set(CMAKE_C_STANDARD 90)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -pedantic-errors")
include_directories(.)
include_directories(src)
include_directories(HeaderFiles)

add_executable(Progetto
        src/game.c
        HeaderFiles/library.h
        HeaderFiles/pieces.h
        HeaderFiles/players.h src/cpu.c HeaderFiles/cpu.h)

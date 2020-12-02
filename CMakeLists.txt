cmake_minimum_required(VERSION 3.15)
project(Maze)

set(CMAKE_CXX_STANDARD 14)

add_executable(Maze main.cpp)

set(CMAKE_EXE_LINKER_FLAGS "-static-libgcc -static-libstdc++")
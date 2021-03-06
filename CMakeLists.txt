cmake_minimum_required(VERSION 3.17)
project(tetris)

set(CMAKE_CXX_STANDARD 20)

add_executable(tetris main.cpp Collisions.h CoordinateSystem.h Tetrimino.h)

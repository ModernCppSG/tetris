cmake_minimum_required(VERSION 3.17)
project(tetris)

set(CMAKE_CXX_STANDARD 20)

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

add_executable(${PROJECT_NAME} main.cpp internal_clock.cpp tetris_types.h)

target_link_libraries(${PROJECT_NAME} PRIVATE Threads::Threads)

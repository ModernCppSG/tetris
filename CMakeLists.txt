cmake_minimum_required(VERSION 3.17)
project(tetris)

set(CMAKE_CXX_STANDARD 20)
enable_testing()

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)
find_package(GTest REQUIRED)

add_executable(${PROJECT_NAME} main.cpp internal_clock.cpp)
add_executable(tetris_test tests/test_refframes.cpp)

target_link_libraries(${PROJECT_NAME} PRIVATE Threads::Threads)
target_link_libraries(tetris_test PRIVATE Threads::Threads GTest::gtest GTest::gtest_main)
gtest_discover_tests(tetris_test)

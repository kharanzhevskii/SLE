cmake_minimum_required(VERSION 3.20)
project(CMakeTest)

find_package(GTest REQUIRED)

enable_testing()
add_executable(run_test test.cpp tridiagonal.cpp main.cpp)
target_link_libraries(run_test GTest::gtest_main)

add_test(Alltest run_test)

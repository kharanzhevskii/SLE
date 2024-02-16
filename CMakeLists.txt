cmake_minimum_required(VERSION 3.20)
project(tridiag)

add_subdirectory(src)

if (WITH_TESTS)
    enable_testing()
    add_subdirectory(test)
endif ()

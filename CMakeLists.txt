cmake_minimum_required(VERSION 3.29)
project(lab1)

set(CMAKE_CXX_STANDARD 20)

add_executable(lab1 main.cpp
        smrtptr.hpp
        linked_list.hpp
        smrtptr_tests.cpp
        smrtptr_test.hpp
)

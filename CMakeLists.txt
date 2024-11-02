cmake_minimum_required(VERSION 3.29)
project(lab1)

set(CMAKE_CXX_STANDARD 20)

add_executable(lab1 main.cpp
        smrt_ptr.hpp
        linked_list.hpp
        smrt_ptr_tests.cpp
        smrt_ptr_tests.hpp
)

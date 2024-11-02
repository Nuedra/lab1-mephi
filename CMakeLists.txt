cmake_minimum_required(VERSION 3.29)
project(lab1)

set(CMAKE_CXX_STANDARD 20)

add_executable(lab1 main.cpp
        smrt_ptr.hpp
        linked_list.hpp
        smrt_ptr_tests.cpp
        smrt_ptr_tests.hpp
        graphic.cpp
        graphic.hpp
)

set(SFML_DIR "C:\\Users\\Vladislav\\CLionProjects\\lib\\GCC 13.1.0 MinGW (SEH) - 64-bit\\SFML-2.6.1\\lib\\cmake\\SFML")

target_link_libraries(lab1 sfml-graphics)

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake_modules")
find_package(SFML 2.5 REQUIRED graphics network audio window system)
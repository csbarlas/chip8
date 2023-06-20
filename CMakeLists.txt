# Tutorial for using CMake and GTest:
# https://raymii.org/s/tutorials/Cpp_project_setup_with_cmake_and_unit_tests.html#toc_1

cmake_minimum_required(VERSION 3.0.0)
project(chip8 VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 14)

include_directories(src)

add_subdirectory(src)
add_subdirectory(test)
add_subdirectory(lib/googletest)

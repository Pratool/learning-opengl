# This CMake build system assumes to find dependencies with find_package().
# Read external/README.md for info on building and installing dependencies.

cmake_minimum_required(VERSION 3.10)

project(LearningOpenGL)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()
set(CMAKE_CXX_STANDARD 17)

add_subdirectory(glad)
add_subdirectory(window)

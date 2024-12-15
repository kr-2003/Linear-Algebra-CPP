# Specify the minimum CMake version
cmake_minimum_required(VERSION 3.10)

# Project name and language
project(Matrix2Test LANGUAGES CXX)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add the executable
add_executable(Matrix2Test test_matrix.cpp)
add_executable(VectorTest test_vector.cpp)

# Include the directory containing the Matrix2.h file
target_include_directories(Matrix2Test PRIVATE ${CMAKE_SOURCE_DIR})

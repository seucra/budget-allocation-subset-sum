cmake_minimum_required(VERSION 3.10)
project(SubsetSumCLI)

# Set the C++ standard to C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Define the executable and its source files
add_executable(solver src/main.cpp src/solver.cpp)

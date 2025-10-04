cmake_minimum_required(VERSION 3.10)
project(budget_module)

# Find Python and pybind11
find_package(Python3 REQUIRED COMPONENTS Interpreter Development)
find_package(pybind11 REQUIRED)

# Include directories
include_directories(${Python3_INCLUDE_DIRS} include)

# Source files
set(SOURCES
    src/algorithms/brute_force.cpp
    src/algorithms/greedy.cpp
    src/bindings.cpp
)

# Create shared library
pybind11_add_module(budget_module ${SOURCES})

# Link libraries
target_link_libraries(budget_module PRIVATE ${Python3_LIBRARIES})

cmake_minimum_required(VERSION 3.10)
project(budget_lib LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_BUILD_TYPE Debug)

# -----------------------------------------------------------------------------
# Include directories
# -----------------------------------------------------------------------------
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

# -----------------------------------------------------------------------------
# Shared library (C++ core)
# -----------------------------------------------------------------------------
add_library(budget SHARED
    src/algorithms/brute_force.cpp
    src/algorithms/dp.cpp
    src/algorithms/greedy.cpp
    src/algorithms/backtracking.cpp
    src/algorithms/hybrid.cpp
)

# -----------------------------------------------------------------------------
# Test executable
# -----------------------------------------------------------------------------
add_executable(test_budget src/main.cpp)
target_link_libraries(test_budget PRIVATE budget)

# -----------------------------------------------------------------------------
# Enable warnings
# -----------------------------------------------------------------------------
target_compile_options(budget PRIVATE -Wall -Wextra -Wpedantic)
target_compile_options(test_budget PRIVATE -Wall -Wextra -Wpedantic)

# -----------------------------------------------------------------------------
# Python bindings via pybind11
# -----------------------------------------------------------------------------

# Required Python components
find_package(Python COMPONENTS Interpreter Development REQUIRED)

# Try to find pybind11 using CMake config (recommended if installed via pip or system package)
find_package(pybind11 CONFIG QUIET)

# Fallback: try pkg-config
if(NOT pybind11_FOUND)
    message(WARNING "pybind11 not found via CMake config. Trying pkg-config fallback...")

    find_package(PkgConfig REQUIRED)
    pkg_check_modules(pybind11 REQUIRED IMPORTED_TARGET pybind11)
    add_library(pybind11::pybind11 ALIAS PkgConfig::pybind11)
endif()

# Python module built with pybind11
pybind11_add_module(budget_module
    src/bindings.cpp
    src/algorithms/brute_force.cpp
    src/algorithms/dp.cpp
    src/algorithms/greedy.cpp
    src/algorithms/backtracking.cpp
    src/algorithms/hybrid.cpp
)

target_link_libraries(budget_module PRIVATE pybind11::pybind11)


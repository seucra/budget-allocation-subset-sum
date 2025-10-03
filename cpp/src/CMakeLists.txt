cmake_minimum_required(VERSION 3.10)

project(budget_allocation LANGUAGES CXX)

# Set C++ standard to 17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)  # for shared libs

# Use full absolute paths for source and include dirs
get_filename_component(PROJECT_ROOT_DIR "${CMAKE_CURRENT_SOURCE_DIR}" ABSOLUTE)
set(ALGORITHMS_DIR "${PROJECT_ROOT_DIR}/algorithms")

# Include directories for headers
include_directories(
    "${PROJECT_ROOT_DIR}"
    "${ALGORITHMS_DIR}"
)

# List all source files with full paths
set(ALGO_SRCS
    "${ALGORITHMS_DIR}/brute_force.cpp"
    "${ALGORITHMS_DIR}/dp.cpp"
    "${ALGORITHMS_DIR}/backtracking.cpp"
    "${ALGORITHMS_DIR}/greedy.cpp"
    "${ALGORITHMS_DIR}/hybrid.cpp"
    "${PROJECT_ROOT_DIR}/budget_lib.cpp"
)

# Create shared library 'budget'
add_library(budget SHARED ${ALGO_SRCS})

# Add warnings (optional but recommended)
target_compile_options(budget PRIVATE -Wall -Wextra -Wpedantic)

# Set include directories for the 'budget' target explicitly (modern CMake)
target_include_directories(budget PUBLIC
    "${PROJECT_ROOT_DIR}"
    "${ALGORITHMS_DIR}"
)

# Build the test executable from main.cpp
add_executable(test_budget "${PROJECT_ROOT_DIR}/main.cpp")

# Link the test executable against the shared library
target_link_libraries(test_budget PRIVATE budget)

# Optional: add compile options to test executable as well
target_compile_options(test_budget PRIVATE -Wall -Wextra -Wpedantic)


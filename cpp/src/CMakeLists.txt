cmake_minimum_required(VERSION 3.10)
project(budget_allocation)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})        # so #include "budget_lib.h" works
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/algorithms)

# Gather algorithm sources
set(ALGO_SRCS
    algorithms/brute_force.cpp
    algorithms/dp.cpp
    algorithms/backtracking.cpp
    algorithms/greedy.cpp
    algorithms/hybrid.cpp
    budget_lib.cpp
)

add_library(budget SHARED ${ALGO_SRCS})

add_executable(test_budget main.cpp)
target_link_libraries(test_budget budget)


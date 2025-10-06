// src/DataModel/SolverResult.h
#pragma once

#include <vector>
#include <chrono>

struct SolverResult {
    bool solution_exists = false;
    // Now stores all found subsets
    std::vector<std::vector<int>> subsets; 
    std::chrono::duration<double, std::milli> execution_time;
};

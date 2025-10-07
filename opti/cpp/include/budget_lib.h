#ifndef BUDGET_LIB_H
#define BUDGET_LIB_H

#include <vector>
#include <chrono>
#include <cstdint>

struct Result {
    std::vector<int> indices;  // 0-based indices of selected projects
    int total_cost = 0;
    double execution_time_ms = 0.0;
    double memory_used_mb = 0.0;  // Estimated memory usage
};

#include "brute_force.h"
#include "dp.h"
#include "greedy.h"
#include "backtracking.h"
#include "hybrid.h"

#endif // BUDGET_LIB_H

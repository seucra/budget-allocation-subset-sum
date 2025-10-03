#ifndef BUDGET_LIB_CPP_H
#define BUDGET_LIB_CPP_H

#include <vector>

struct Result {
    std::vector<int> indices;
    int total_cost;
    double execution_time_ms;
    double memory_used_mb;
};

Result run_brute_force(const std::vector<int>& costs, int budget);
Result run_dp(const std::vector<int>& costs, int budget);
Result run_greedy(const std::vector<int>& costs, int budget);
Result run_backtracking(const std::vector<int>& costs, int budget);
Result run_hybrid(const std::vector<int>& costs, int budget);

#endif // BUDGET_LIB_CPP_H


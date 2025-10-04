#include "greedy.h"
#include <chrono>

Result greedy_subset_sum(const std::vector<double>& costs, double budget) {
    Result result;
    auto start = std::chrono::high_resolution_clock::now();

    double total_cost = 0.0;
    for (size_t i = 0; i < costs.size(); ++i) {
        if (total_cost + costs[i] <= budget) {
            result.indices.push_back(i);
            total_cost += costs[i];
        }
    }

    auto end = std::chrono::high_resolution_clock::now();
    result.total_cost = total_cost;
    result.execution_time = std::chrono::duration<double>(end - start).count();

    return result;
}

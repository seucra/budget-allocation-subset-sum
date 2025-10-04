#include "brute_force.h"
#include <chrono>

Result brute_force_subset_sum(const std::vector<double>& costs, double budget) {
    Result result;
    auto start = std::chrono::high_resolution_clock::now();

    std::vector<int> best_indices;
    double best_cost = 0.0;
    int n = costs.size();

    // Try all subsets (2^n) using bitmask
    for (int mask = 0; mask < (1 << n); ++mask) {
        double current_cost = 0.0;
        std::vector<int> current_indices;
        for (int i = 0; i < n; ++i) {
            if (mask & (1 << i)) {
                current_cost += costs[i];
                current_indices.push_back(i);
            }
        }
        if (current_cost <= budget && current_cost > best_cost) {
            best_cost = current_cost;
            best_indices = current_indices;
        }
    }

    auto end = std::chrono::high_resolution_clock::now();
    result.indices = best_indices;
    result.total_cost = best_cost;
    result.execution_time = std::chrono::duration<double>(end - start).count();

    return result;
}

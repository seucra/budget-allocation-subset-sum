#include "brute_force.h"
#include <chrono>

Result brute_force_subset_sum(const std::vector<int>& costs, int budget) {
    int n = (int)costs.size();
    int best_sum = 0;
    std::vector<int> best_subset;

    auto start = std::chrono::high_resolution_clock::now();

    int total_subsets = 1 << n;
    for (int mask = 0; mask < total_subsets; ++mask) {
        int current_sum = 0;
        std::vector<int> current_subset;
        for (int i = 0; i < n; ++i) {
            if (mask & (1 << i)) {
                current_sum += costs[i];
                current_subset.push_back(i);
            }
        }
        if (current_sum <= budget && current_sum > best_sum) {
            best_sum = current_sum;
            best_subset = current_subset;
        }
    }

    auto end = std::chrono::high_resolution_clock::now();
    double duration_ms = std::chrono::duration<double, std::milli>(end - start).count();

    return {best_subset, best_sum, duration_ms, 0.0};
}


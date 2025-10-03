// algorithms/brute_force.cpp
#include "brute_force.h"
#include <chrono>
#include <algorithm>

Result run_brute_force(const std::vector<int>& costs, int budget) {
    auto start = std::chrono::high_resolution_clock::now();

    int n = (int)costs.size();
    long long best_sum = 0;
    std::vector<int> best_subset;

    // If n is large, this will be infeasible — caller should avoid calling brute force for large n.
    if (n <= 0) {
        Result r{{}, 0, 0.0, 0.0};
        return r;
    }
    // Prevent shifting overflow for n >= 31 on 32-bit ints: use unsigned long long for mask
    unsigned long long total_subsets = 1ULL << n;
    if (n >= 63) total_subsets = 0; // avoid trying to iterate monstrous counts

    // If n >= 63, we bail early (too large)
    if (n >= 63) {
        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double, std::milli> dur = end - start;
        return {{}, 0, dur.count(), 0.0};
    }

    for (unsigned long long mask = 0; mask < total_subsets; ++mask) {
        long long sum = 0;
        std::vector<int> subset;
        for (int i = 0; i < n; ++i) {
            if (mask & (1ULL << i)) {
                sum += costs[i];
                if (sum > budget) break; // small pruning
                subset.push_back(i);
            }
        }
        if (sum <= budget && sum > best_sum) {
            best_sum = sum;
            best_subset = subset;
            if (best_sum == budget) break; // perfect fit
        }
    }

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> dur = end - start;

    return {best_subset, (int)best_sum, dur.count(), 0.0};
}


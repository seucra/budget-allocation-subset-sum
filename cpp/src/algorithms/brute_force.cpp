#include "../include/budget_lib.h"
#include <cstdint>
#include <vector>
#include <chrono>

Result run_brute_force(const std::vector<int>& costs, int budget) {
    auto start = std::chrono::high_resolution_clock::now();

    int n = costs.size();
    if (n <= 0 || budget <= 0 || n > 20) return {{}, 0, 0.0, 0.0};

    int max_sum = 0;
    std::vector<int> best_selected;
    std::vector<int> selected;
    selected.reserve(n);

    uint64_t total = 1ULL << n;
    for (uint64_t mask = 0; mask < total; ++mask) {
        int sum = 0;
        selected.clear();
        bool valid = true;

        for (int i = 0; i < n; ++i) {
            if (mask & (1ULL << i)) {
                if (costs[i] <= 0) {
                    valid = false;
                    break;
                }
                sum += costs[i];
                if (sum > budget) {
                    valid = false;
                    break;
                }
                selected.push_back(i);
            }
        }

        if (!valid) continue;

        if (sum > max_sum || 
            (sum == max_sum && 
             (selected.size() < best_selected.size() || 
              (selected.size() == best_selected.size() && selected < best_selected)))) {
            max_sum = sum;
            best_selected = selected;
            if (max_sum == budget) break;
        }
    }

    double mem_mb = n * sizeof(int) / (1024.0 * 1024.0);
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> dur = end - start;
    return {best_selected, max_sum, dur.count(), mem_mb};
}

#include "backtracking.h"
#include <chrono>
#include <vector>

void backtrack(const std::vector<int>& costs, int budget, int idx,
               int current_sum, std::vector<int>& current_set,
               int& best_sum, std::vector<int>& best_set) {
    if (current_sum > best_sum && current_sum <= budget) {
        best_sum = current_sum;
        best_set = current_set;
    }
    if (idx == (int)costs.size() || current_sum >= budget) return;

    // Choose idx
    if (current_sum + costs[idx] <= budget) {
        current_set.push_back(idx);
        backtrack(costs, budget, idx + 1, current_sum + costs[idx], current_set, best_sum, best_set);
        current_set.pop_back();
    }
    // Don't choose idx
    backtrack(costs, budget, idx + 1, current_sum, current_set, best_sum, best_set);
}

Result backtracking_subset_sum(const std::vector<int>& costs, int budget) {
    auto start = std::chrono::high_resolution_clock::now();

    int best_sum = 0;
    std::vector<int> best_set;
    std::vector<int> current_set;

    backtrack(costs, budget, 0, 0, current_set, best_sum, best_set);

    auto end = std::chrono::high_resolution_clock::now();
    double duration_ms = std::chrono::duration<double, std::milli>(end - start).count();

    return {best_set, best_sum, duration_ms, 0.0};
}


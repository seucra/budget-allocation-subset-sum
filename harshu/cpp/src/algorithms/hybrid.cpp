#include "hybrid.h"
#include <chrono>
#include <vector>
#include <algorithm>
#include <functional>

// Reuse backtracking from above, but limit search space using greedy prefilter

void hybrid_backtrack(const std::vector<int>& costs, int budget, int idx,
                      int current_sum, std::vector<int>& current_set,
                      int& best_sum, std::vector<int>& best_set) {
    if (current_sum > best_sum && current_sum <= budget) {
        best_sum = current_sum;
        best_set = current_set;
    }
    if (idx == (int)costs.size() || current_sum >= budget) return;

    if (current_sum + costs[idx] <= budget) {
        current_set.push_back(idx);
        hybrid_backtrack(costs, budget, idx + 1, current_sum + costs[idx], current_set, best_sum, best_set);
        current_set.pop_back();
    }
    hybrid_backtrack(costs, budget, idx + 1, current_sum, current_set, best_sum, best_set);
}

Result hybrid_subset_sum(const std::vector<int>& costs, int budget) {
    auto start = std::chrono::high_resolution_clock::now();

    // Use greedy to select a promising subset
    int n = (int)costs.size();
    std::vector<int> indices(n);
    for (int i = 0; i < n; ++i) indices[i] = i;

    std::sort(indices.begin(), indices.end(), [&](int a, int b) {
        return costs[a] < costs[b];
    });

    std::vector<int> filtered_costs;
    std::vector<int> filtered_indices;

    int total = 0;
    for (int idx : indices) {
        if (total + costs[idx] <= budget) {
            total += costs[idx];
            filtered_costs.push_back(costs[idx]);
            filtered_indices.push_back(idx);
        } else {
            break;
        }
    }

    // Backtrack on the filtered list for better optimization
    int best_sum = 0;
    std::vector<int> best_set;
    std::vector<int> current_set;

    // Because filtered_costs is a subset, indexes here correspond to filtered_indices
    std::function<void(int, int)> backtrack_func = [&](int pos, int curr_sum) {
        if (curr_sum > best_sum && curr_sum <= budget) {
            best_sum = curr_sum;
            best_set = current_set;
        }
        if (pos == (int)filtered_costs.size() || curr_sum >= budget) return;

        // Choose
        if (curr_sum + filtered_costs[pos] <= budget) {
            current_set.push_back(filtered_indices[pos]);
            backtrack_func(pos + 1, curr_sum + filtered_costs[pos]);
            current_set.pop_back();
        }
        // Don't choose
        backtrack_func(pos + 1, curr_sum);
    };

    backtrack_func(0, 0);

    auto end = std::chrono::high_resolution_clock::now();
    double duration_ms = std::chrono::duration<double, std::milli>(end - start).count();

    return {best_set, best_sum, duration_ms, 0.0};
}


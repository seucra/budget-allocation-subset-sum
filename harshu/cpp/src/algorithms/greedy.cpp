#include "greedy.h"
#include <chrono>
#include <vector>
#include <algorithm>

Result greedy_subset_sum(const std::vector<int>& costs, int budget) {
    auto start = std::chrono::high_resolution_clock::now();

    // Sort indices by cost ascending
    int n = (int)costs.size();
    std::vector<int> indices(n);
    for (int i = 0; i < n; ++i) indices[i] = i;

    std::sort(indices.begin(), indices.end(), [&](int a, int b) {
        return costs[a] < costs[b];
    });

    std::vector<int> selected_indices;
    int total = 0;
    for (int idx : indices) {
        if (total + costs[idx] <= budget) {
            total += costs[idx];
            selected_indices.push_back(idx);
        } else {
            break;
        }
    }

    auto end = std::chrono::high_resolution_clock::now();
    double duration_ms = std::chrono::duration<double, std::milli>(end - start).count();

    return {selected_indices, total, duration_ms, 0.0};
}


#include "../include/budget_lib.h"
#include <algorithm>

Result run_greedy(const std::vector<int>& costs, int budget) {
    auto start = std::chrono::high_resolution_clock::now();

    if (budget <= 0 || costs.empty()) {
        return {{}, 0, 0.0, 0.0};
    }

    // Sort costs ascending
    std::vector<std::pair<int, int>> ordered;
    for (size_t i = 0; i < costs.size(); ++i) {
        if (costs[i] > 0) ordered.emplace_back(costs[i], i);
    }
    std::sort(ordered.begin(), ordered.end());

    std::vector<int> selected;
    int sum = 0;
    for (const auto& p : ordered) {
        if (sum + p.first <= budget) {
            sum += p.first;
            selected.push_back(p.second);
        }
    }

    // Basic memory estimate (vectors only)
    double mem_mb = (costs.size() * sizeof(int) + selected.size() * sizeof(int)) / (1024.0 * 1024.0);

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> dur = end - start;

    std::sort(selected.begin(), selected.end());  // Sort indices for consistency
    return {selected, sum, dur.count(), mem_mb};
}

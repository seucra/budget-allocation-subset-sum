#include "../include/budget_lib.h"
#include <algorithm>
#include <vector>
#include <chrono>

Result run_dp(const std::vector<int>& costs, int budget) {
    auto start = std::chrono::high_resolution_clock::now();

    if (budget <= 0 || costs.empty()) return {{}, 0, 0.0, 0.0};

    int n = costs.size();
    std::vector<int> dp(budget + 1, 0);
    std::vector<std::vector<int>> selected(budget + 1);

    for (int i = 0; i < n; ++i) {
        if (costs[i] <= 0) continue;
        for (int w = budget; w >= costs[i]; --w) {
            int candidate_sum = dp[w - costs[i]] + costs[i];
            if (candidate_sum > dp[w] || 
                (candidate_sum == dp[w] && 
                 (selected[w - costs[i]].size() + 1 < selected[w].size() || 
                  (selected[w - costs[i]].size() + 1 == selected[w].size() && selected[w - costs[i]] < selected[w])))) {
                dp[w] = candidate_sum;
                selected[w] = selected[w - costs[i]];
                selected[w].push_back(i);
            }
        }
    }

    int best_sum = 0;
    std::vector<int> best_indices;
    for (int w = budget; w >= 0; --w) {
        if (dp[w] > best_sum || 
            (dp[w] == best_sum && 
             (selected[w].size() < best_indices.size() || 
              (selected[w].size() == best_indices.size() && selected[w] < best_indices)))) {
            best_sum = dp[w];
            best_indices = selected[w];
        }
    }

    std::sort(best_indices.begin(), best_indices.end());
    double mem_mb = (budget + 1) * (sizeof(int) + sizeof(std::vector<int>)) / (1024.0 * 1024.0);
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> dur = end - start;

    return {best_indices, best_sum, dur.count(), mem_mb};
}

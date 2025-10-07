#include "dp.h"
#include <chrono>
#include <vector>
#include <algorithm>

Result dp_subset_sum(const std::vector<int>& costs, int budget) {
    int n = (int)costs.size();

    auto start = std::chrono::high_resolution_clock::now();

    // dp[i][j] = true if sum j is possible with first i items
    std::vector<std::vector<bool>> dp(n + 1, std::vector<bool>(budget + 1, false));
    dp[0][0] = true;

    for (int i = 1; i <= n; ++i) {
        int cost = costs[i - 1];
        for (int j = 0; j <= budget; ++j) {
            if (j >= cost)
                dp[i][j] = dp[i - 1][j] || dp[i - 1][j - cost];
            else
                dp[i][j] = dp[i - 1][j];
        }
    }

    // Find best sum <= budget
    int best_sum = 0;
    for (int j = budget; j >= 0; --j) {
        if (dp[n][j]) {
            best_sum = j;
            break;
        }
    }

    // Backtrack to find selected indices
    std::vector<int> selected_indices;
    int w = best_sum;
    for (int i = n; i > 0 && w > 0; --i) {
        if (!dp[i - 1][w]) {
            selected_indices.push_back(i - 1);
            w -= costs[i - 1];
        }
    }
    std::reverse(selected_indices.begin(), selected_indices.end());

    auto end = std::chrono::high_resolution_clock::now();
    double duration_ms = std::chrono::duration<double, std::milli>(end - start).count();

    return {selected_indices, best_sum, duration_ms, 0.0};
}


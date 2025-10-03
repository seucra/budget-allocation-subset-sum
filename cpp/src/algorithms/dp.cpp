// algorithms/dp.cpp
#include "dp.h"
#include <chrono>
#include <algorithm>

Result run_dp(const std::vector<int>& costs, int budget) {
    auto start = std::chrono::high_resolution_clock::now();

    int n = (int)costs.size();
    if (budget < 0) budget = 0;
    // Use bitset-like DP but as vector<char> to reduce memory for large budgets
    std::vector<char> dp(budget + 1, 0);
    std::vector<std::vector<char>> take; // for backtracking - optional tradeoff: memory heavy
    dp[0] = 1;

    // To backtrack, store parent info: previous reachable states for each item index.
    // We'll use a vector of vectors<int> parent that marks which previous sum leads to current.
    // Simpler: record a 2D dp (bool) if budget * n reasonable. For safety, we'll record prev choice indexes.
    std::vector<std::vector<int>> prev(n + 1, std::vector<int>(budget + 1, -1));
    std::vector<std::vector<char>> dp2(n + 1, std::vector<char>(budget + 1, 0));
    dp2[0][0] = 1;

    for (int i = 1; i <= n; ++i) {
        int c = costs[i - 1];
        for (int w = 0; w <= budget; ++w) {
            if (dp2[i - 1][w]) {
                dp2[i][w] = 1;
                // don't set prev since not taking
            }
            if (w >= c && dp2[i - 1][w - c]) {
                dp2[i][w] = 1;
                prev[i][w] = 1; // mark that i was used to reach w
            }
        }
    }

    int best = 0;
    for (int w = budget; w >= 0; --w) {
        if (dp2[n][w]) { best = w; break; }
    }

    std::vector<int> selected;
    int w = best;
    for (int i = n; i > 0 && w > 0; --i) {
        if (prev[i][w] == 1) {
            selected.push_back(i - 1);
            w -= costs[i - 1];
        }
    }
    std::reverse(selected.begin(), selected.end());

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> dur = end - start;
    return {selected, best, dur.count(), 0.0};
}


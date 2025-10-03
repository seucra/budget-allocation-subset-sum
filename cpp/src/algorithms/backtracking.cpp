// algorithms/backtracking.cpp
#include "backtracking.h"
#include <chrono>

struct BTState {
    int best_sum = 0;
    std::vector<int> best_subset;

    // NEW: add a counter to limit recursive calls
    int call_count = 0;
    const int MAX_CALLS = 1'000'000;  // 1 million calls
};

void bt_helper(const std::vector<int>& costs, int budget, int idx, int current_sum,
               std::vector<int>& current, BTState& state) {

        // ✅ Stop if too many recursive calls
    if (++state.call_count > state.MAX_CALLS) return;

    if (current_sum > budget) return;
    if (current_sum > state.best_sum) {
        state.best_sum = current_sum;
        state.best_subset = current;
    }
    if (idx >= (int)costs.size()) return;

    // Bound: if current_sum + remaining_possible <= state.best_sum, prune
    // Compute optimistic remaining sum quickly (not exact but simple): sum of remaining items
    // (optional improvement omitted for speed of compile)

    // Choose include
    current.push_back(idx);
    bt_helper(costs, budget, idx + 1, current_sum + costs[idx], current, state);
    current.pop_back();

    // Exclude
    bt_helper(costs, budget, idx + 1, current_sum, current, state);
}

Result run_backtracking(const std::vector<int>& costs, int budget) {
    auto start = std::chrono::high_resolution_clock::now();

    BTState state;
    std::vector<int> cur;
    bt_helper(costs, budget, 0, 0, cur, state);

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> dur = end - start;
    return {state.best_subset, state.best_sum, dur.count(), 0.0};
}


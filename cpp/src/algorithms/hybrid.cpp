// algorithms/hybrid.cpp
#include "hybrid.h"
#include "greedy.h"
#include "backtracking.h"
#include <chrono>
#include <algorithm>    // for std::sort
#include <functional>   // for std::function

Result hybrid_subset_sum(const std::vector<int>& costs, int budget) {
    auto start = std::chrono::high_resolution_clock::now();

    // Step 1: Greedy baseline
    Result g = greedy_subset_sum(costs, budget);
    int best_sum = g.total_cost;
    std::vector<int> best_subset = g.selected_indices;

    int n = (int)costs.size();

    // Choose a small candidate window K
    int K = std::min(n, 15);

    // Prepare pairs (cost, index)
    std::vector<std::pair<int,int>> order;
    order.reserve(n);
    for (int i = 0; i < n; ++i) {
        order.emplace_back(costs[i], i);
    }
    std::sort(order.begin(), order.end());

    // Candidate indices
    std::vector<int> cand_idx;
    cand_idx.reserve(K);
    for (int i = 0; i < K; ++i) {
        cand_idx.push_back(order[i].second);
    }
    // Candidate costs in same order
    std::vector<int> cand_costs;
    cand_costs.reserve(K);
    for (int idx : cand_idx) {
        cand_costs.push_back(costs[idx]);
    }

    // Local backtracking on small candidate set
    struct LocalState {
        int best_sum = 0;
        std::vector<int> best_subset;
    };
    LocalState ls;
    std::vector<int> cur;

    // Lambda with correct capture
    std::function<void(int, int)> local_bt = [&](int idx, int cur_sum) {
        if (cur_sum > budget) return;
        if (cur_sum > ls.best_sum) {
            ls.best_sum = cur_sum;
            ls.best_subset = cur;
        }
        if (idx >= K) return;

        // include
        cur.push_back(idx);
        local_bt(idx + 1, cur_sum + cand_costs[idx]);
        cur.pop_back();
        // exclude
        local_bt(idx + 1, cur_sum);
    };

    local_bt(0, 0);

    // Translate local best subset indices to original indices
    std::vector<int> local_selection;
    int local_sum = 0;
    for (int c : ls.best_subset) {
        int orig = cand_idx[c];
        local_selection.push_back(orig);
        local_sum += costs[orig];
    }

    if (local_sum > best_sum && local_sum <= budget) {
        best_sum = local_sum;
        best_subset = std::move(local_selection);
    }

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> dur = end - start;
    return {best_subset, best_sum, dur.count(), 0.0};
}


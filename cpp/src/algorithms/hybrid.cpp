#include "../include/budget_lib.h"
#include "../include/greedy.h"
#include <algorithm>
#include <functional>

Result run_hybrid(const std::vector<int>& costs, int budget) {
    auto start = std::chrono::high_resolution_clock::now();

    if (budget <= 0 || costs.empty()) return {{}, 0, 0.0, 0.0};

    Result greedy_res = run_greedy(costs, budget);
    int best_sum = greedy_res.total_cost;
    std::vector<int> best_selected = greedy_res.indices;

    int k = std::min(static_cast<int>(costs.size()), 10);
    std::vector<std::pair<int, int>> ordered;
    for (size_t i = 0; i < costs.size(); ++i) {
        if (costs[i] > 0) ordered.emplace_back(costs[i], i);
    }
    std::sort(ordered.begin(), ordered.end());
    std::vector<int> cand_costs, cand_indices;
    for (int i = 0; i < k && i < static_cast<int>(ordered.size()); ++i) {
        cand_costs.push_back(ordered[i].first);
        cand_indices.push_back(ordered[i].second);
    }

    struct LocalState {
        int best_sum = 0;
        std::vector<int> best_subset;
    };
    LocalState ls;
    std::vector<int> cur_selected;
    std::function<void(int, int)> local_bt = [&](int idx, int cur_sum) {
        if (cur_sum > budget) return;
        if (cur_sum > ls.best_sum || 
            (cur_sum == ls.best_sum && 
             (cur_selected.size() < ls.best_subset.size() || 
              (cur_selected.size() == ls.best_subset.size() && cur_selected < ls.best_subset)))) {
            ls.best_sum = cur_sum;
            ls.best_subset = cur_selected;
        }
        if (idx >= static_cast<int>(cand_costs.size())) return;

        cur_selected.push_back(cand_indices[idx]);
        local_bt(idx + 1, cur_sum + cand_costs[idx]);
        cur_selected.pop_back();
        local_bt(idx + 1, cur_sum);
    };
    local_bt(0, 0);

    if (ls.best_sum > best_sum && ls.best_sum <= budget) {
        best_sum = ls.best_sum;
        best_selected = ls.best_subset;
    }

    double mem_mb = (costs.size() * sizeof(int) + cand_costs.size() * sizeof(int) +
                     ls.best_subset.size() * sizeof(int)) / (1024.0 * 1024.0);
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> dur = end - start;
    return {best_selected, best_sum, dur.count(), mem_mb};
}

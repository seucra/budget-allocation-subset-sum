#include "../include/budget_lib.h"
#include <vector>
#include <chrono>

void bt_helper(const std::vector<int>& costs, int budget, int idx, int cur_sum, 
               std::vector<int>& cur_selected, int& max_sum, std::vector<int>& best_selected, 
               int& call_count, const int max_calls = 1000000) {
    if (call_count++ > max_calls) return;
    if (cur_sum > budget) return;
    if (cur_sum > max_sum || 
        (cur_sum == max_sum && 
         (cur_selected.size() < best_selected.size() || 
          (cur_selected.size() == best_selected.size() && cur_selected < best_selected)))) {
        max_sum = cur_sum;
        best_selected = cur_selected;
    }
    if (idx >= static_cast<int>(costs.size())) return;

    if (costs[idx] > 0) {
        cur_selected.push_back(idx);
        bt_helper(costs, budget, idx + 1, cur_sum + costs[idx], cur_selected, max_sum, best_selected, call_count, max_calls);
        cur_selected.pop_back();
    }
    bt_helper(costs, budget, idx + 1, cur_sum, cur_selected, max_sum, best_selected, call_count, max_calls);
}

Result run_backtracking(const std::vector<int>& costs, int budget) {
    auto start = std::chrono::high_resolution_clock::now();

    if (budget <= 0 || costs.empty()) return {{}, 0, 0.0, 0.0};

    int max_sum = 0;
    std::vector<int> best_selected, cur_selected;
    int call_count = 0;
    bt_helper(costs, budget, 0, 0, cur_selected, max_sum, best_selected, call_count);

    double mem_mb = costs.size() * sizeof(int) / (1024.0 * 1024.0);
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> dur = end - start;
    return {best_selected, max_sum, dur.count(), mem_mb};
}

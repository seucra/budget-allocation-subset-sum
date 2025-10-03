#include "budget_lib.h"

Result run_brute_force(const std::vector<int>& costs, int budget) {
    return brute_force_subset_sum(costs, budget);
}

Result run_dp(const std::vector<int>& costs, int budget) {
    return dp_subset_sum(costs, budget);
}

Result run_backtracking(const std::vector<int>& costs, int budget) {
    return backtracking_subset_sum(costs, budget);
}

Result run_greedy(const std::vector<int>& costs, int budget) {
    return greedy_subset_sum(costs, budget);
}

Result run_hybrid(const std::vector<int>& costs, int budget) {
    return hybrid_subset_sum(costs, budget);
}


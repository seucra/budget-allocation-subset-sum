#include "../include/budget_lib.h"
#include <iostream>
#include <string>

void print_result(const Result& res, const std::string& algo_name) {
    std::cout << "Algorithm: " << algo_name << "\n";
    std::cout << "Total Cost: " << res.total_cost << "\n";
    std::cout << "Execution Time: " << res.execution_time_ms << "ms\n";
    std::cout << "Memory Used: " << res.memory_used_mb << "MB\n";
    std::cout << "Selected Indices: ";
    for (int i : res.indices) std::cout << i << " ";
    std::cout << "\n\n";
}

int main() {
    std::vector<int> costs = {10, 20, 30, 40};
    int budget = 50;

    print_result(run_brute_force(costs, budget), "Brute Force");
    print_result(run_dp(costs, budget), "Dynamic Programming");
    print_result(run_greedy(costs, budget), "Greedy");
    print_result(run_backtracking(costs, budget), "Backtracking");
    print_result(run_hybrid(costs, budget), "Hybrid");

    return 0;
}

#include <iostream>
#include <vector>
#include <iomanip>
#include "budget_lib.h"

void print_result(const std::string& name, const Result& res) {
    std::cout << "Algorithm: " << name << "\n";
    std::cout << "  Total Cost: " << res.total_cost << "\n";
    std::cout << "  Selected Indices: ";
    for (int idx : res.selected_indices)
        std::cout << idx << " ";
    std::cout << "\n";
    std::cout << "  Execution Time: " << std::fixed << std::setprecision(3)
              << res.execution_time_ms << " ms\n";
    std::cout << "  Memory Used: " << res.memory_used_mb << " MB\n\n";
}

int main() {
    std::vector<int> project_costs = {120, 80, 150, 40, 60, 90, 110};
    int budget = 300;

    std::cout << "=== Budget Allocation Subset Sum Test ===\n";
    std::cout << "Budget: " << budget << "\n";
    std::cout << "Projects: ";
    for (int cost : project_costs) std::cout << cost << " ";
    std::cout << "\n\n";

    print_result("Brute Force", run_brute_force(project_costs, budget));
    print_result("Dynamic Programming", run_dp(project_costs, budget));
    print_result("Backtracking", run_backtracking(project_costs, budget));
    print_result("Greedy Heuristic", run_greedy(project_costs, budget));
    print_result("Hybrid (Greedy + Backtracking)", run_hybrid(project_costs, budget));

    return 0;
}


#// main.cpp
#include <iostream>
#include <vector>
#include <random>
#include <numeric>

#include "budget_lib.h"

std::vector<int> generate_random_projects(int n, int min_cost = 10, int max_cost = 500) {
    std::vector<int> projects;
    projects.reserve(n);
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(min_cost, max_cost);
    for (int i = 0; i < n; ++i) projects.push_back(dist(gen));
    return projects;
}

void print_result(const Result& r, const std::string& name) {
    std::cout << "Algorithm: " << name << '\n';
    std::cout << "  Total Cost: " << r.total_cost << '\n';
    std::cout << "  Selected Count: " << r.selected_indices.size() << '\n';
    std::cout << "  Execution Time (ms): " << r.execution_time_ms << '\n';
    std::cout << "  Memory Used (MB): " << r.memory_used_mb << '\n';
    std::cout << '\n';
}

int main() {
    const int N = 500;            // change as needed
    auto projects = generate_random_projects(N, 10, 500);
    long long total = std::accumulate(projects.begin(), projects.end(), 0LL);
    int budget = static_cast<int>(total * 60 / 100);

    std::cout << "Generated projects: " << N << '\n';
    std::cout << "Total cost: " << total << '\n';
    std::cout << "Budget (60%): " << budget << "\n\n";

    // IMPORTANT: avoid calling brute force if N is large (brute_force has internal guard)
    print_result(run_greedy(projects, budget), "Greedy Heuristic");
    print_result(run_hybrid(projects, budget), "Hybrid (greedy + local search)");
    print_result(run_dp(projects, budget), "Dynamic Programming");
    print_result(run_backtracking(projects, budget), "Backtracking");
    print_result(run_brute_force(projects, budget), "Brute Force");

    return 0;
}

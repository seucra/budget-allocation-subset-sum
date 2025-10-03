// main.cpp
#include <iostream>
#include <vector>
#include <random>
#include <string>

#include "budget_lib.h"

// Generate random project costs
std::vector<int> generate_random_projects(int n, int min_cost = 10, int max_cost = 500) {
    std::vector<int> projects;
    projects.reserve(n);
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(min_cost, max_cost);
    for (int i = 0; i < n; ++i) {
        projects.push_back(dist(gen));
    }
    return projects;
}

// Print results
void print_result(const CResult& r, const std::string& name) {
    std::cout << "Algorithm: " << name << "\n";
    std::cout << "  Total Cost: " << r.total_cost << '\n';
    std::cout << "  Selected Count: " << r.count << '\n';
    std::cout << "  Execution Time (ms): " << r.exec_time << '\n';

    std::cout << "  Selected indices: ";
    for (int i = 0; i < r.count; ++i) {
        std::cout << r.indices[i] << " ";
    }
    std::cout << "\n\n";
}

int main() {
    // Generate some random projects and define a budget
    std::vector<int> projects = generate_random_projects(20, 10, 500);
    int budget = 1500;

    CResult r;

    r = run_greedy_c(projects.data(), projects.size(), budget);
    print_result(r, "Greedy Heuristic");
    free_result(r);

    r = run_hybrid_c(projects.data(), projects.size(), budget);
    print_result(r, "Hybrid (greedy + local search)");
    free_result(r);

    r = run_dp_c(projects.data(), projects.size(), budget);
    print_result(r, "Dynamic Programming");
    free_result(r);

    r = run_backtracking_c(projects.data(), projects.size(), budget);
    print_result(r, "Backtracking");
    free_result(r);

    r = run_brute_force_c(projects.data(), projects.size(), budget);
    print_result(r, "Brute Force");
    free_result(r);

    return 0;
}


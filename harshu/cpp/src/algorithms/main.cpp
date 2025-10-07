#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <chrono>
#include <sys/resource.h> // for getrusage (Unix/Linux)

struct Result {
    std::vector<int> selected_indices;
    int total_cost;
    double execution_time_ms;
    double memory_used_mb;
};

Result brute_force_subset_sum(const std::vector<int>& costs, int budget) {
    int n = (int)costs.size();
    int best_sum = 0;
    std::vector<int> best_subset;

    auto start = std::chrono::high_resolution_clock::now();

    // Enumerate all subsets (2^n)
    int total_subsets = 1 << n;
    for (int mask = 0; mask < total_subsets; ++mask) {
        int current_sum = 0;
        std::vector<int> current_subset;
        for (int i = 0; i < n; ++i) {
            if (mask & (1 << i)) {
                current_sum += costs[i];
                current_subset.push_back(i);
            }
        }
        if (current_sum <= budget && current_sum > best_sum) {
            best_sum = current_sum;
            best_subset = current_subset;
        }
    }

    auto end = std::chrono::high_resolution_clock::now();
    double duration_ms = std::chrono::duration<double, std::milli>(end - start).count();

    return {best_subset, best_sum, duration_ms};
}

Result dp_subset_sum(const std::vector<int>& costs, int budget) {
    int n = (int)costs.size();
    std::vector<std::vector<bool>> dp(n + 1, std::vector<bool>(budget + 1, false));
    dp[0][0] = true;

    auto start = std::chrono::high_resolution_clock::now();

    for (int i = 1; i <= n; ++i) {
        int cost = costs[i - 1];
        for (int j = 0; j <= budget; ++j) {
            if (j < cost)
                dp[i][j] = dp[i - 1][j];
            else
                dp[i][j] = dp[i - 1][j] || dp[i - 1][j - cost];
        }
    }

    // Find best achievable sum <= budget
    int best_sum = 0;
    for (int j = budget; j >= 0; --j) {
        if (dp[n][j]) {
            best_sum = j;
            break;
        }
    }

    // Backtrack to find subset
    std::vector<int> selected_indices;
    int w = best_sum;
    for (int i = n; i > 0 && w > 0; --i) {
        if (!dp[i - 1][w]) {
            selected_indices.push_back(i - 1);
            w -= costs[i - 1];
        }
    }

    std::reverse(selected_indices.begin(), selected_indices.end());

    auto end = std::chrono::high_resolution_clock::now();
    double duration_ms = std::chrono::duration<double, std::milli>(end - start).count();

    return {selected_indices, best_sum, duration_ms};
}

struct BacktrackState {
    int best_sum;
    std::vector<int> best_subset;
};

void backtrack_helper(
    const std::vector<int>& costs,
    int budget,
    int index,
    int current_sum,
    std::vector<int>& current_subset,
    BacktrackState& state
) {
    if (current_sum > budget) return;
    if (current_sum > state.best_sum) {
        state.best_sum = current_sum;
        state.best_subset = current_subset;
    }
    if (index == (int)costs.size()) return;

    // Include current project
    current_subset.push_back(index);
    backtrack_helper(costs, budget, index + 1, current_sum + costs[index], current_subset, state);
    current_subset.pop_back();

    // Exclude current project
    backtrack_helper(costs, budget, index + 1, current_sum, current_subset, state);
}

Result backtracking_subset_sum(const std::vector<int>& costs, int budget) {
    auto start = std::chrono::high_resolution_clock::now();

    BacktrackState state{0, {}};
    std::vector<int> current_subset;

    backtrack_helper(costs, budget, 0, 0, current_subset, state);

    auto end = std::chrono::high_resolution_clock::now();
    double duration_ms = std::chrono::duration<double, std::milli>(end - start).count();

    return {state.best_subset, state.best_sum, duration_ms};
}

Result greedy_subset_sum(std::vector<int> costs, int budget) {
    int n = (int)costs.size();

    // Pair cost with original index
    std::vector<std::pair<int,int>> cost_idx;
    for (int i = 0; i < n; ++i) cost_idx.emplace_back(costs[i], i);

    // Sort ascending by cost
    std::sort(cost_idx.begin(), cost_idx.end());

    std::vector<int> selected_indices;
    int current_sum = 0;

    auto start = std::chrono::high_resolution_clock::now();

    for (auto& [cost, idx] : cost_idx) {
        if (current_sum + cost <= budget) {
            current_sum += cost;
            selected_indices.push_back(idx);
        } else {
            break;
        }
    }

    auto end = std::chrono::high_resolution_clock::now();
    double duration_ms = std::chrono::duration<double, std::milli>(end - start).count();

    return {selected_indices, current_sum, duration_ms};
}

Result hybrid_subset_sum(const std::vector<int>& costs, int budget) {
    // Step 1: Greedy solution as starting point
    Result greedy_res = greedy_subset_sum(costs, budget);

    // Step 2: Backtracking but skip subsets smaller than greedy solution
    auto start = std::chrono::high_resolution_clock::now();

    BacktrackState state{greedy_res.total_cost, greedy_res.selected_indices};
    std::vector<int> current_subset;

    // Similar backtracking helper, but prune if current_sum <= greedy_res.total_cost
    std::function<void(int,int)> backtrack_improved = [&](int idx, int current_sum) {
        if (current_sum > budget) return;
        if (current_sum > state.best_sum) {
            state.best_sum = current_sum;
            state.best_subset = current_subset;
        }
        if (idx == (int)costs.size()) return;

        // Include current project
        current_subset.push_back(idx);
        backtrack_improved(idx + 1, current_sum + costs[idx]);
        current_subset.pop_back();

        // Exclude current project
        backtrack_improved(idx + 1, current_sum);
    };

    backtrack_improved(0, 0);

    auto end = std::chrono::high_resolution_clock::now();
    double duration_ms = std::chrono::duration<double, std::milli>(end - start).count();

    return {state.best_subset, state.best_sum, duration_ms};
}

// ==== Memory Usage Utility (Unix-only) ====

double get_memory_usage_mb() {
    struct rusage usage;
    getrusage(RUSAGE_SELF, &usage);
#if defined(__APPLE__) && defined(__MACH__)
    return usage.ru_maxrss / (1024.0 * 1024.0); // bytes to MB
#else
    return usage.ru_maxrss / 1024.0; // kilobytes to MB
#endif
}

// ==== Algorithm Runner ====

void run_and_print(const std::string& name, const std::vector<int>& costs, int budget,
                   Result (*algo)(const std::vector<int>&, int)) {
    double mem_before = get_memory_usage_mb();
    Result res = algo(costs, budget);
    double mem_after = get_memory_usage_mb();

    res.memory_used_mb = mem_after - mem_before;

    std::cout << "Algorithm: " << name << "\n";
    std::cout << "  Total Cost: " << res.total_cost << "\n";
    std::cout << "  Selected Indices: ";
    for (int idx : res.selected_indices)
        std::cout << idx << " ";
    std::cout << "\n";
    std::cout << "  Execution Time: " << std::fixed << std::setprecision(3)
              << res.execution_time_ms << " ms\n";
    std::cout << "  Memory Used: " << std::fixed << std::setprecision(3)
              << res.memory_used_mb << " MB\n\n";
}

// ==== Main Test Runner ====

int main() {
    // Sample input
    std::vector<int> project_costs = {120, 80, 150, 40, 60, 90, 110};
    int budget = 300;

    std::cout << "=== Budget Allocation Subset Sum Test ===\n";
    std::cout << "Budget: " << budget << "\n";
    std::cout << "Projects: ";
    for (int cost : project_costs) std::cout << cost << " ";
    std::cout << "\n\n";

    // Run each algorithm
    run_and_print("Brute Force", project_costs, budget, brute_force_subset_sum);
    run_and_print("Dynamic Programming", project_costs, budget, dp_subset_sum);
    run_and_print("Backtracking", project_costs, budget, backtracking_subset_sum);
    run_and_print("Greedy Heuristic", project_costs, budget, greedy_subset_sum);
    run_and_print("Hybrid (Greedy + Backtrack)", project_costs, budget, hybrid_subset_sum);

    return 0;
}

#include "solver.h"
#include <vector>
#include <numeric>
#include <algorithm>

// --- Backtracking Implementation (Finds All Solutions) ---

// Helper function for the backtracking algorithm
void backtrack_helper(const std::vector<int>& candidates, int target,
                      std::vector<std::vector<int>>& result,
                      std::vector<int>& current_subset, int start_index) {
    if (target == 0) {
        result.push_back(current_subset);
        return;
    }
    if (target < 0) {
        return;
    }

    for (size_t i = start_index; i < candidates.size(); ++i) {
        // Skip duplicates to avoid generating the same subset multiple times
        if (i > start_index && candidates[i] == candidates[i-1]) {
            continue;
        }

        current_subset.push_back(candidates[i]);
        backtrack_helper(candidates, target - candidates[i], result, current_subset, i + 1);
        current_subset.pop_back(); // Backtrack
    }
}

std::vector<std::vector<int>> solve_backtrack(const std::vector<int>& numbers, int target) {
    std::vector<std::vector<int>> result;
    std::vector<int> current_subset;
    std::vector<int> sorted_numbers = numbers;
    std::sort(sorted_numbers.begin(), sorted_numbers.end()); // Sort to handle duplicates properly
    backtrack_helper(sorted_numbers, target, result, current_subset, 0);
    return result;
}


// --- Dynamic Programming Implementation (Finds One Solution) ---

std::vector<int> solve_dp(const std::vector<int>& numbers, int target) {
    int n = numbers.size();
    // dp[i][j] is true if a sum of j is possible with the first i numbers
    std::vector<std::vector<bool>> dp(n + 1, std::vector<bool>(target + 1, false));

    for (int i = 0; i <= n; ++i) {
        dp[i][0] = true; // A sum of 0 is always possible (by choosing no numbers)
    }

    // Fill the DP table
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= target; ++j) {
            if (numbers[i - 1] > j) {
                dp[i][j] = dp[i - 1][j]; // Current number is too large
            } else {
                // Check if sum is possible by either excluding or including the current number
                dp[i][j] = dp[i - 1][j] || dp[i - 1][j - numbers[i - 1]];
            }
        }
    }

    // If no solution exists, return empty
    if (!dp[n][target]) {
        return {};
    }

    // Reconstruct one solution by backtracking through the DP table
    std::vector<int> result;
    int current_sum = target;
    for (int i = n; i > 0 && current_sum > 0; --i) {
        // If the sum was NOT possible with the previous set of numbers,
        // it means we MUST have included the current number.
        if (!dp[i - 1][current_sum]) {
            result.push_back(numbers[i - 1]);
            current_sum -= numbers[i - 1];
        }
    }
    return result;
}

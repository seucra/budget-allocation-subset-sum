// src/CoreSolver/DpSolver.cpp
#include "DpSolver.h"
#include <vector>
#include <chrono>
#include <stdexcept>

SolverResult DpSolver::solve(const DataSet& data, bool find_all) {
    if (find_all) {
        throw std::logic_error("DP solver does not support 'find all' mode. Use the 'backtrack' algorithm instead.");
    }

    auto start_time = std::chrono::high_resolution_clock::now();
    
    const auto& nums = data.numbers;
    int target = data.target_sum;
    int n = nums.size();

    std::vector<std::vector<bool>> dp(n + 1, std::vector<bool>(target + 1, false));
    for (int i = 0; i <= n; ++i) dp[i][0] = true;

    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= target; ++j) {
            if (nums[i - 1] > j) {
                dp[i][j] = dp[i - 1][j];
            } else {
                dp[i][j] = dp[i - 1][j] || dp[i - 1][j - nums[i - 1]];
            }
        }
    }
    
    SolverResult result;
    if (dp[n][target]) {
        result.solution_exists = true;
        std::vector<int> subset;
        int curr_sum = target;
        for (int i = n; i > 0 && curr_sum > 0; --i) {
            if (dp[i][curr_sum] && !dp[i - 1][curr_sum]) {
                subset.push_back(nums[i - 1]);
                curr_sum -= nums[i - 1];
            }
        }
        result.subsets.push_back(subset);
    }

    auto end_time = std::chrono::high_resolution_clock::now();
    result.execution_time = end_time - start_time;
    return result;
}

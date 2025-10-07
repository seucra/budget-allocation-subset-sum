#ifndef SOLVER_H
#define SOLVER_H

#include <vector>
#include <string>

/**
 * @brief Finds all subsets that sum to the target using backtracking.
 * @param numbers The set of numbers to choose from.
 * @param target The target sum.
 * @return A vector containing all solution subsets.
 */
std::vector<std::vector<int>> solve_backtrack(const std::vector<int>& numbers, int target);

/**
 * @brief Finds ONE subset that sums to the target using dynamic programming.
 * @param numbers The set of numbers to choose from.
 * @param target The target sum.
 * @return A vector representing one solution subset. Returns an empty vector if no solution exists.
 */
std::vector<int> solve_dp(const std::vector<int>& numbers, int target);

#endif // SOLVER_H

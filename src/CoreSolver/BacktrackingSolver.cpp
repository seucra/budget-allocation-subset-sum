// src/CoreSolver/BacktrackingSolver.cpp
#include "BacktrackingSolver.h"
#include <chrono>

void BacktrackingSolver::findSubsetsRecursive(const std::vector<int>& nums, int target, size_t index, 
                                                std::vector<int>& current_subset, 
                                                SolverResult& result, bool find_all) {
    // This is the correct way to stop the search early if we only need one solution.
    if (!find_all && result.solution_exists) {
        return;
    }

    // Base Case 1: A solution is found.
    // We record it and MUST return to prevent the function from exploring deeper from this point
    // which would cause duplicates.
    if (target == 0) {
        result.solution_exists = true;
        result.subsets.push_back(current_subset);
        return; 
    }

    // Base Case 2: The path is invalid (sum is too large or we're out of numbers).
    if (target < 0 || index >= nums.size()) {
        return; 
    }

    // --- Explore ---
    // 1. Include the element at the current index.
    current_subset.push_back(nums[index]);
    findSubsetsRecursive(nums, target - nums[index], index + 1, current_subset, result, find_all);
    
    // 2. Backtrack (remove the element) to explore the other path.
    current_subset.pop_back();

    // 3. Exclude the element at the current index.
    findSubsetsRecursive(nums, target, index + 1, current_subset, result, find_all);
}

SolverResult BacktrackingSolver::solve(const DataSet& data, bool find_all) {
    auto start_time = std::chrono::high_resolution_clock::now();
    
    SolverResult result;
    std::vector<int> current_subset;
    
    findSubsetsRecursive(data.numbers, data.target_sum, 0, current_subset, result, find_all);

    auto end_time = std::chrono::high_resolution_clock::now();
    result.execution_time = end_time - start_time;
    return result;
}

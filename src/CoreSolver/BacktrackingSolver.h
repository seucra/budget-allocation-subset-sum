/// src/CoreSolver/BacktrackingSolver.h
#pragma once
#include "SubsetSumSolver.h"

class BacktrackingSolver : public ISubsetSumSolver {
public:
    SolverResult solve(const DataSet& data, bool find_all = false) override;

private:
    void findSubsetsRecursive(const std::vector<int>& nums, int target, size_t index, 
                              std::vector<int>& current_subset, 
                              SolverResult& result, bool find_all);
};

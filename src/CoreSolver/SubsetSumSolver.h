// src/CoreSolver/SubsetSumSolver.h
#pragma once

#include "DataModel/DataSet.h"
#include "DataModel/SolverResult.h"

class ISubsetSumSolver {
public:
    virtual ~ISubsetSumSolver() = default;
    // Added find_all parameter to switch between finding one or all solutions
    virtual SolverResult solve(const DataSet& data, bool find_all = false) = 0;
};

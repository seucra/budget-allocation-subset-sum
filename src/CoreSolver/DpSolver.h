// src/CoreSolver/DpSolver.h
#pragma once
#include "SubsetSumSolver.h"

class DpSolver : public ISubsetSumSolver {
public:
    SolverResult solve(const DataSet& data, bool find_all = false) override;
};

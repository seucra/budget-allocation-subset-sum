// src/AlgorithmSelector/SolverFactory.h
#pragma once

#include "CoreSolver/SubsetSumSolver.h"
#include <string>
#include <memory>

class SolverFactory {
public:
    static std::unique_ptr<ISubsetSumSolver> createSolver(const std::string& type);
};

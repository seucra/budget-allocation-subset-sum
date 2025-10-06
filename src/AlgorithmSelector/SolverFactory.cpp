// src/AlgorithmSelector/SolverFactory.cpp
#include "SolverFactory.h"
#include <stdexcept>

// Include the new header files for our concrete solver classes
#include "CoreSolver/DpSolver.h" 
#include "CoreSolver/BacktrackingSolver.h"

std::unique_ptr<ISubsetSumSolver> SolverFactory::createSolver(const std::string& type) {
    if (type == "dp") {
        return std::make_unique<DpSolver>();
    }
    if (type == "backtrack") {
        return std::make_unique<BacktrackingSolver>();
    }
    throw std::invalid_argument("Unknown solver type: " + type);
}

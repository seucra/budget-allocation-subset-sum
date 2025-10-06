// src/Benchmarking/Benchmark.h
#pragma once

#include "CoreSolver/SubsetSumSolver.h"
#include "DataModel/DataSet.h"
#include <chrono>

struct BenchmarkResult {
    int iterations;
    int solutions_found_count; // How many runs found at least one solution
    std::chrono::duration<double, std::milli> total_time;
    std::chrono::duration<double, std::milli> average_time;
};

class BenchmarkRunner {
public:
    static BenchmarkResult run(ISubsetSumSolver& solver, const DataSet& data, 
                               int iterations, bool find_all);
};

// src/Benchmarking/Benchmark.cpp
#include "Benchmark.h"

BenchmarkResult BenchmarkRunner::run(ISubsetSumSolver& solver, const DataSet& data, 
                                     int iterations, bool find_all) {
    BenchmarkResult bench_result;
    bench_result.iterations = iterations;
    bench_result.solutions_found_count = 0;
    bench_result.total_time = std::chrono::duration<double, std::milli>(0);

    for (int i = 0; i < iterations; ++i) {
        SolverResult result = solver.solve(data, find_all);
        bench_result.total_time += result.execution_time;
        if (result.solution_exists) {
            bench_result.solutions_found_count++;
        }
    }

    if (iterations > 0) {
        bench_result.average_time = bench_result.total_time / iterations;
    } else {
        bench_result.average_time = std::chrono::duration<double, std::milli>(0);
    }
    
    return bench_result;
}

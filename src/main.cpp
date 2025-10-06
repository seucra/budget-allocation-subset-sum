// src/main.cpp
#include <cstdint>
#include <iostream>
#include <vector>
#include <string>
#include <memory>
#include <stdexcept>
#include <fstream>

#include "cxxopts.hpp"
#include "AlgorithmSelector/SolverFactory.h"
#include "Benchmarking/Benchmark.h"
#include "DBLayer/DatabaseManager.h"

// ... (All helper functions like print_solver_result, parse_numbers_string, etc. are unchanged) ...
void print_solver_result(const SolverResult& result);
void print_benchmark_result(const BenchmarkResult& result);
std::vector<int> parse_numbers_string(const std::string& s);
DataSet parse_from_file(const std::string& filename);


int main(int argc, char** argv) {
    cxxopts::Options options("SubsetSumSolver", "A tool to solve the subset sum problem.");

    options.add_options()
        // ... (existing options are unchanged) ...
        ("a,algo", "Algorithm to use (dp, backtrack)", cxxopts::value<std::string>()->default_value("dp"))
        ("n,numbers", "Comma-separated list of numbers", cxxopts::value<std::string>())
        ("t,target", "The target sum", cxxopts::value<int>())
        ("f,file", "Path to an input file", cxxopts::value<std::string>())
        ("find-all", "Find all possible subsets (backtrack only)", cxxopts::value<bool>()->default_value("false"))
        ("b,benchmark", "Run benchmark N times", cxxopts::value<int>())
        ("h,help", "Print usage")
        // --- NEW OPTION ---
        ("s,save", "Save the result to the database", cxxopts::value<bool>()->default_value("false"));
    
    try {
        auto result = options.parse(argc, argv);

        if (result.count("help")) {
            std::cout << options.help() << std::endl;
            return 0;
        }

        DataSet problem_data;
        // ... (Input parsing logic is unchanged) ...
        bool has_file = result.count("file") > 0;
        bool has_direct_input = result.count("numbers") > 0 && result.count("target") > 0;
        if (has_file && has_direct_input) throw std::runtime_error("Please provide input via --file OR --numbers/--target, not both.");
        if (has_file) problem_data = parse_from_file(result["file"].as<std::string>());
        else if (has_direct_input) {
            problem_data.numbers = parse_numbers_string(result["numbers"].as<std::string>());
            problem_data.target_sum = result["target"].as<int>();
        } else {
             throw std::runtime_error("No input provided. Use --file or --numbers and --target.");
        }
        
        std::string algo_type = result["algo"].as<std::string>();
        auto solver = SolverFactory::createSolver(algo_type);
        bool find_all = result["find-all"].as<bool>();
        bool save_to_db = result["save"].as<bool>();
        
        std::cout << "Using algorithm: " << algo_type << std::endl;
        
        if (result.count("benchmark")) {
            if(save_to_db) std::cout << "Note: --save is ignored in benchmark mode." << std::endl;
            int iterations = result["benchmark"].as<int>();
            if (iterations <= 0) throw std::runtime_error("Benchmark iterations must be positive.");
            BenchmarkResult bench_result = BenchmarkRunner::run(*solver, problem_data, iterations, find_all);
            print_benchmark_result(bench_result);
        } else {
            // --- SINGLE SOLVER RUN ---
            SolverResult solver_result = solver->solve(problem_data, find_all);
            print_solver_result(solver_result);

            // --- SAVE TO DATABASE IF REQUESTED ---
            if (save_to_db) {
                std::cout << "\nAttempting to save result to database..." << std::endl;
                // Use your user/password here
                std::string conn_string = "dbname=subset_solver_db user=user1 password=password1";
                DatabaseManager db_manager(conn_string);
                db_manager.connect();
                db_manager.saveResult(problem_data, solver_result, algo_type);
            }
        }

    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}


// --- PASTE THE UNCHANGED HELPER FUNCTIONS HERE ---
// (print_solver_result, print_benchmark_result, parse_numbers_string, parse_from_file)
void print_solver_result(const SolverResult& result) { std::cout << "--- Solver Results ---\n" << "Execution Time: " << result.execution_time.count() << " ms\n"; if (result.solution_exists) { std::cout << "Solutions Found: " << result.subsets.size() << "\n"; int count = 1; for (const auto& subset : result.subsets) { std::cout << "  Subset " << count++ << ": { "; for (size_t i = 0; i < subset.size(); ++i) { std::cout << subset[i] << (i == subset.size() - 1 ? "" : ", "); } std::cout << " }\n"; } } else { std::cout << "Solution Found: No\n"; } std::cout << "----------------------\n"; }
void print_benchmark_result(const BenchmarkResult& result) { std::cout << "--- Benchmark Results ---\n" << "Total Iterations: " << result.iterations << "\n" << "Runs with Solutions: " << result.solutions_found_count << " / " << result.iterations << "\n" << "Total Execution Time: " << result.total_time.count() << " ms\n" << "Average Execution Time: " << result.average_time.count() << " ms\n" << "-------------------------\n"; }
std::vector<int> parse_numbers_string(const std::string& s) { std::vector<int> numbers; if (s.empty()) return numbers; std::stringstream ss(s); std::string item; while (std::getline(ss, item, ',')) { try { numbers.push_back(std::stoi(item)); } catch (const std::invalid_argument& e) { throw std::runtime_error("'" + item + "' is not a valid integer."); } } return numbers; }
DataSet parse_from_file(const std::string& filename) { std::ifstream file(filename); if (!file.is_open()) { throw std::runtime_error("Could not open file '" + filename + "'"); } DataSet data; std::string line; if (std::getline(file, line)) { data.numbers = parse_numbers_string(line); } else { throw std::runtime_error("File is empty or could not read numbers line."); } if (std::getline(file, line)) { try { data.target_sum = std::stoi(line); } catch (const std::invalid_argument& e) { throw std::runtime_error("Invalid target sum on the second line."); } } else { throw std::runtime_error("Could not read target sum from file."); } return data; }

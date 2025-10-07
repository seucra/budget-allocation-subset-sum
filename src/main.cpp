#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <chrono>
#include <iomanip>
#include "solver.h"

// --- Helper Functions ---

void print_usage() {
    std::cerr << "Usage: ./solver --algo <backtrack|dp> --numbers <n1,n2,...> --target <sum>\n";
    std::cerr << "Example: ./solver --algo backtrack --numbers 1,2,3,4,5 --target 6\n";
}

std::vector<int> parse_numbers(const std::string& s) {
    std::vector<int> numbers;
    std::stringstream ss(s);
    std::string item;
    while (std::getline(ss, item, ',')) {
        try {
            numbers.push_back(std::stoi(item));
        } catch (const std::exception& e) {
            std::cerr << "Error: Invalid number format in numbers list.\n";
            exit(EXIT_FAILURE);
        }
    }
    return numbers;
}

void print_solutions(const std::vector<std::vector<int>>& solutions) {
    if (solutions.empty()) {
        std::cout << "  No solutions found.\n";
        return;
    }
    int count = 1;
    for (const auto& subset : solutions) {
        std::cout << "  Subset " << count++ << ": { ";
        for (size_t i = 0; i < subset.size(); ++i) {
            std::cout << subset[i] << (i == subset.size() - 1 ? "" : ", ");
        }
        std::cout << " }\n";
    }
}

// --- Main Execution ---

int main(int argc, char* argv[]) {
    if (argc != 7) {
        print_usage();
        return 1;
    }

    std::string algo;
    std::vector<int> numbers;
    int target = 0;

    for (int i = 1; i < argc; i += 2) {
        std::string flag = argv[i];
        if (i + 1 >= argc) { print_usage(); return 1; }
        std::string value = argv[i + 1];

        if (flag == "--algo") algo = value;
        else if (flag == "--numbers") numbers = parse_numbers(value);
        else if (flag == "--target") target = std::stoi(value);
        else { print_usage(); return 1; }
    }

    if (algo != "backtrack" && algo != "dp") {
        std::cerr << "Error: Invalid algorithm. Choose 'backtrack' or 'dp'.\n";
        return 1;
    }

    std::cout << "Using algorithm: " << algo << "\n";
    std::cout << "--- Solver Results ---\n";

    auto start = std::chrono::high_resolution_clock::now();

    if (algo == "backtrack") {
        auto solutions = solve_backtrack(numbers, target);
        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double, std::milli> elapsed = end - start;

        std::cout << "Execution Time: " << std::fixed << std::setprecision(6) << elapsed.count() << " ms\n";
        std::cout << "Solutions Found: " << solutions.size() << "\n";
        print_solutions(solutions);
    } else if (algo == "dp") {
        auto solution = solve_dp(numbers, target);
        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double, std::milli> elapsed = end - start;

        std::cout << "Execution Time: " << std::fixed << std::setprecision(6) << elapsed.count() << " ms\n";
        if (solution.empty()) {
            std::cout << "Solutions Found: 0\n";
            std::cout << "  No solution found.\n";
        } else {
            std::cout << "Solutions Found: 1\n";
            print_solutions({solution}); // Wrap for print function
        }
    }

    std::cout << "----------------------\n";

    return 0;
}

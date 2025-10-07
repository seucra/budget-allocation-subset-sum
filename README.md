# Subset Sum Solver in C++

![Language](https://img.shields.io/badge/Language-C%2B%2B-blue.svg)
![Build](https://img.shields.io/badge/Build-CMake-green.svg)
![License](https://img.shields.io/badge/License-MIT-yellow.svg)

A command-line tool that solves the classic **Subset Sum Problem** using two distinct algorithmic paradigms: **Backtracking** and **Dynamic Programming**. This project was developed as part of a 3rd-semester "Analysis of Algorithms" course to practically demonstrate and compare these approaches.



---

## ## 🚀 Project Overview

The Subset Sum Problem asks whether a subset of a given set of integers sums up to a specific target value. This project provides a CLI tool to:
1.  Parse a set of numbers and a target sum from the command line.
2.  Solve the problem using a chosen algorithm.
3.  Display the solution(s) found and the execution time.

The primary goal is to serve as an educational tool to contrast an exhaustive search method (Backtracking) with a pseudo-polynomial time method (Dynamic Programming).

---

## ## ⚙️ Algorithmic Approaches

This solver implements two fundamentally different ways to tackle the subset sum problem.

### ### Backtracking

* **Strategy:** An exhaustive, recursive search. It builds a solution step-by-step and abandons any path ("backtracks") as soon as it determines the path cannot lead to a valid solution.
* **Output:** Finds **all possible subsets** that sum to the target.
* **Complexity:** $O(2^n)$, where $n$ is the number of items. Its performance degrades rapidly as the size of the input set grows.

### ### Dynamic Programming

* **Strategy:** A bottom-up approach that solves the problem by breaking it down into simpler subproblems. It uses a 2D table to store whether a certain sum is achievable with a subset of the items, avoiding redundant calculations.
* **Output:** This implementation is optimized to confirm the **existence** of a solution and returns only **one valid subset**.
* **Complexity:** $O(n \times \text{target})$, where $n$ is the number of items and `target` is the target sum. This is a pseudo-polynomial time complexity.

---

## ## 🛠️ Getting Started

### ### Prerequisites

* A C++ compiler (g++, Clang)
* CMake (version 3.10 or higher)

### ### Building the Project

Clone the repository and run the following commands from the project's root directory:
```bash
mkdir build
cd build
cmake ..
make
````

An executable named `solver` will be created in the `build` directory.

-----

## \#\# ⌨️ Usage

The tool is run from the command line with the following syntax:

```bash
./solver --algo <algorithm> --numbers <num1,num2,...> --target <sum>
```

  * `--algo`: The algorithm to use (`backtrack` or `dp`).
  * `--numbers`: A comma-separated list of integers with no spaces.
  * `--target`: The integer sum to find.

-----

## \#\# 📊 Examples & Demonstrations

Here are a few curated problems designed to showcase the behavior of each algorithm.

### \#\#\# 1. The Basic Case

A simple problem to verify basic functionality.

  * **Problem:** Numbers = `{1,2,3,4,5}`, Target = `6`

  * **Backtracking:** Finds all three solutions.

    ```bash
    ./solver --algo backtrack --numbers 1,2,3,4,5 --target 6
    # --- Solver Results ---
    # Solutions Found: 3
    #   Subset 1: { 1, 2, 3 }
    #   Subset 2: { 1, 5 }
    #   Subset 3: { 2, 4 }
    ```

  * **Dynamic Programming:** Finds one valid solution.

    ```bash
    ./solver --algo dp --numbers 1,2,3,4,5 --target 6
    # --- Solver Results ---
    # Solutions Found: 1
    #   Subset 1: { 3, 2, 1 }
    ```

  * **Analysis:** A straightforward demonstration of backtracking's enumerative power versus DP's single-solution approach.

### \#\#\# 2. The Multi-Length Case

This case highlights how the algorithms handle solutions of different sizes.

  * **Problem:** Numbers = `{3,4,5,7,8,10,12}`, Target = `20`

  * **Backtracking:** Finds all five solutions, including ones with 2, 3, and 4 items.

    ```bash
    ./solver --algo backtrack --numbers 3,4,5,7,8,10,12 --target 20
    # --- Solver Results ---
    # Solutions Found: 5
    #   Subset 1: { 3, 4, 5, 8 }
    #   Subset 2: { 3, 5, 12 }
    #   ... (and 3 more)
    ```

  * **Dynamic Programming:** Finds a single, valid 4-item solution.

    ```bash
    ./solver --algo dp --numbers 3,4,5,7,8,10,12 --target 20
    # --- Solver Results ---
    # Solutions Found: 1
    #   Subset 1: { 8, 5, 4, 3 }
    ```

  * **Analysis:** This proves that our DP implementation is not optimized to find the *shortest* subset (`{8, 12}`), only a *valid* one. This is a crucial distinction in its design.

### \#\#\# 3. The Performance Test (The "Aha\!" Moment)

This large problem is designed to push backtracking to its limit, clearly demonstrating the practical performance difference.

  * **Problem:** A set of 35 numbers, Target = `1642`

  * **Dynamic Programming:** Finishes almost instantly.

    ```bash
        ./solver --algo dp --numbers 91,112,121,133,158,176,199,203,219,222,245,255,280,291,301,310,313,332,343,351,360,366,389,391,404,416,423,431,444,459,468,471,488,490,499 --target 1642

    # --- Solver Results ---
    # Execution Time: 0.853211 ms
    # Solutions Found: 1
    #   Subset 1: { 301, 255, 219, 176, 112, 91, 488 }
    ```

  * **Backtracking:** Will run for a very long time (minutes, or indefinitely).

    ```bash
        ./solver --algo backtrack --numbers 91,112,121,133,158,176,199,203,219,222,245,255,280,291,301,310,313,332,343,351,360,366,389,391,404,416,423,431,444,459,468,471,488,490,499 --target 1642

    # (Execution will hang as it searches 2^35 combinations...)
    # (Requires Ctrl+C to terminate)
    ```

  * **Analysis:** This is the definitive demonstration. Backtracking's $O(2^n)$ complexity makes it infeasible for larger sets, while DP's $O(n \times \text{target})$ complexity remains highly efficient, solving the problem in under a millisecond.

-----

## \#\# 📁 Project Structure

```
.
├── CMakeLists.txt
├── README.md
└── src
    ├── main.cpp
    ├── solver.cpp
    └── solver.h
```

-----


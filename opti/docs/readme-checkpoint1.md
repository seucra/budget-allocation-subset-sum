# Read this after reading dev-backend-mustread-revised

---

# Budget Allocation Subset Sum — Development Report (Step 1)

---

## Overview

We are building a **modular C++ shared library** that solves the **Subset Sum Problem** variants for budget allocation. This library will contain multiple algorithms and can be integrated with other systems (e.g., Python APIs) later.

---

## Key Concepts for Everyone

* **Subset Sum Problem (SSP):**
  Given a list of project costs and a budget, select a subset of projects whose total cost best fits the budget without exceeding it.

* **Algorithms:**
  We implement several classic and heuristic algorithms to solve SSP:

  * Brute Force (check all subsets)
  * Dynamic Programming (optimal with memoization)
  * Backtracking (recursive exploration with pruning)
  * Greedy Heuristic (fast, approximate)
  * Hybrid (combines approaches for balance)

* **Shared Library (`.so` / `.dll`):**
  A compiled library containing all algorithms. Other programs can load and call these functions dynamically without recompiling the entire project.

* **Memory and Time Profiling:**
  Measure algorithm performance in execution time (milliseconds) and memory usage (megabytes).

---

## Stepwise Development Breakdown

### Step 1: Modular C++ Code Organization

* **Goal:** Organize code so each algorithm is in its own file (`.cpp` and `.h`).

* **Why:**

  * Easier to maintain and test individual algorithms.
  * Facilitates collaborative development (each teammate can work on different algorithms).
  * Simplifies adding new algorithms or improving existing ones.

* **Files structure:**

  ```
  cpp/src/
  ├── algorithms/
  │   ├── brute_force.cpp / .h
  │   ├── dp.cpp / .h
  │   ├── backtracking.cpp / .h
  │   ├── greedy.cpp / .h
  │   ├── hybrid.cpp / .h
  ├── common.h          # Shared data structures (Result struct)
  ├── budget_lib.cpp    # Library interface exporting all algorithms
  ├── budget_lib.h      # Header declaring library API
  └── main.cpp          # Test harness executable
  ```

---

### Step 2: Defining Common Structures

* We define a **Result struct** holding:

  * Selected project indices
  * Total cost of selected projects
  * Execution time in milliseconds
  * Memory used in megabytes (future use)

This struct is shared across all algorithms for consistent return types.

---

### Step 3: Implementing Algorithms

* Each algorithm implements a function like:

  ```cpp
  Result brute_force_subset_sum(const std::vector<int>& costs, int budget);
  ```

* They return the best subset of projects found, timing info, and (eventually) memory usage.

* **Example: Brute force** tries all subsets (2^n), best for small inputs.

* Other algorithms apply more efficient or approximate strategies.

---

### Step 4: Building the Shared Library

* All algorithms are wrapped in a **library interface** (`budget_lib.cpp/h`) exposing functions like:

  ```cpp
  Result run_brute_force(const std::vector<int>& costs, int budget);
  Result run_dp(const std::vector<int>& costs, int budget);
  ```

* This interface serves as the **single point of access** for all algorithms.

* Compile all `.cpp` files into position-independent code (`-fPIC`), then link into a shared library (`libbudget.so`).

* Shared libraries allow other programs to dynamically load and call our algorithms without recompiling.

---

### Step 5: Creating a Test Harness

* A standalone `main.cpp` is created to:

  * Load sample project costs and budget.
  * Run each algorithm via the shared library interface.
  * Print results: selected projects, total cost, execution time, memory usage.

* This ensures **each algorithm works correctly independently** and provides baseline benchmarks.

---

### Step 6: Build and Run Instructions (Linux Example)

1. Compile each `.cpp` file into object files with position-independent code:

   ```bash
   g++ -std=c++17 -fPIC -c algorithms/brute_force.cpp algorithms/dp.cpp algorithms/backtracking.cpp algorithms/greedy.cpp algorithms/hybrid.cpp budget_lib.cpp
   ```

2. Create the shared library:

   ```bash
   g++ -shared -o libbudget.so brute_force.o dp.o backtracking.o greedy.o hybrid.o budget_lib.o
   ```

3. Compile test executable linking with the shared library:

   ```bash
   g++ -std=c++17 main.cpp -L. -lbudget -o test_budget
   ```

4. Run the test executable:

   ```bash
   LD_LIBRARY_PATH=. ./test_budget
   ```

---

## Important Concepts for Second-Year CS Students

* **Position Independent Code (`-fPIC`):**
  Required for shared libraries to allow code to be loaded at any memory address.

* **Shared Libraries (`.so`, `.dll`):**
  Reusable, dynamically loaded code modules, essential for modularity and integration.

* **Function Prototypes and Headers:**
  Declaring functions in `.h` files ensures other source files can call them correctly.

* **Build Process:**
  Compiling source to object files and linking them into libraries/executables is standard in C++ projects.

---

## What’s Next?

* Automate builds using `Makefile` or `CMake` for easier compilation.

* Integrate the shared library with Python using bindings like `pybind11` or `ctypes`.

* Expand algorithms with priority and risk adjustments.

* Add real-time memory profiling.

---

## Summary

| Aspect           | Description                                                        |
| ---------------- | ------------------------------------------------------------------ |
| Modular code     | Each algorithm in its own `.cpp`/`.h` file                         |
| Shared library   | Compiled `.so` file exporting all algorithm functions              |
| Common interface | `budget_lib.h` exposes all algorithms uniformly                    |
| Test harness     | `main.cpp` runs and benchmarks algorithms                          |
| Build process    | Compile object files → link shared library → build test executable |

---

